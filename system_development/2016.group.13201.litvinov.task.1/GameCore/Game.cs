using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace GameCore {
    public sealed class Game {
        public event EventHandler ScoreChanged;
        public event EventHandler GhostsRelationshipsModeChanged;
        public event EventHandler GameStatusChanged;

        private TickTimer _pursuitModeTimer;

        private void Tick() {
            _pursuitModeTimer.Tick();
        }

        public enum Status {
            Paused,
            Playing,
            GameOver,
            Win
        }

        internal int Score => Pacman?.Score ?? 0;

        private Status _status;
        public Status GameStatus {
            get { return _status; }
            private set {
                if (_status != value) {
                    _status = value;
                    GameStatusChanged?.Invoke(this, EventArgs.Empty);
                }
            }
        }

        private sealed class GameObjectFactory {
            private static bool IsGetLoaderMethod(MethodInfo methodInfo) {
                return
                    "GetLoader".Equals(methodInfo.Name)
                    && methodInfo.IsStatic
                    && methodInfo.ReturnType == typeof(IGameObjectLoader)
                    && methodInfo.GetParameters().Length == 0;
            }

            private readonly Dictionary<char, IGameObjectLoader> _featureTypeToLoader = 
                new Dictionary<char, IGameObjectLoader>();

            internal GameObjectFactory() {
                Assembly gameObjectsAssembly = typeof(GameObject).Assembly;
                foreach (Type assemblyType in gameObjectsAssembly.GetTypes()) {
                    if (assemblyType.IsSubclassOf(typeof(GameObject))) {
                        var loaderMethods = assemblyType.GetMethods().Where(IsGetLoaderMethod).ToList();
                        if (loaderMethods.Count == 0) {
                            continue;
                        }
                        try {
                            IGameObjectLoader loader = loaderMethods.First().Invoke(null, null) as IGameObjectLoader;
                            if (loader != null) {
                                _featureTypeToLoader[loader.GetOriginFeatureType()] = loader;
                            }
                        }
                        catch (Exception) {
                            // ignored
                        }
                    }
                }
            }

            public bool IsSupported(char featureType) {
                return _featureTypeToLoader.ContainsKey(featureType);
            }
            public IGameObjectLoader this[char featureType] => _featureTypeToLoader[featureType];
        }

        private readonly GameObjectFactory _gameObjectFactory = new GameObjectFactory();

        private GameObject ProduceGameObject(char featureType, int objectX, int objectY, Field<GameObject> staticGameObjects) {
            if (_gameObjectFactory.IsSupported(featureType)) {
                GameObjectProducer producer = _gameObjectFactory[featureType].GetProducer();
                if (producer == null) {
                    throw new SystemException("producer can't be null!");
                }
                GameObject gameObject = producer(new PointInt(objectX, objectY), staticGameObjects);
                var dotGameObject = gameObject as DotGameObject;
                if (dotGameObject != null) {
                    _dotsLeftCount++;
                    dotGameObject.OnAnnihilate += OnDotAnnihilate;
                }
                var pacmanGameObject = gameObject as Pacman;
                if (pacmanGameObject != null) {
                    Pacman = pacmanGameObject;
                    Pacman.EnergizerEatEvent += OnPacmanEnergizerEat;
                    Pacman.DieEvent += OnPacmanDie;
                    Pacman.ScoreChanged += (sender, args) => ScoreChanged?.Invoke(this, EventArgs.Empty);
                }
                return gameObject;
            }
            throw new UnsupportedGameObjectException("Неподдерживаемый тип объекта: " + featureType);
        }

        private void OnDotAnnihilate(object sender, EventArgs eventArgs) {
            _dotsLeftCount--;
            if (_dotsLeftCount <= 0) {
                _dotsLeftCount = 0;
                GameStatus = Status.Win;
            }
        }

        private void OnPacmanDie(object sender, EventArgs eventArgs) {
            if (Pacman == null) {
                return;
            }
            if (Pacman.Lives > 0) {
                foreach (Hero h in Heroes) {
                    h.Respawn();
                }
                GameStatus = Status.Paused;
            } else {
                GameStatus = Status.GameOver;
            }
        }

        private void OnPacmanEnergizerEat(object sender, EventArgs eventArgs) {
            GameGhostRelationshipsMode = GhostRelationshipsMode.GhostsAreFood;
            _pursuitModeTimer.Start();
        }

        private GhostRelationshipsMode _ghostRelationshipsMode;

        public void TryUnpause() {
            if (GameStatus == Status.Paused) {
                GameStatus = Status.Playing;
            }
        }

        private GhostRelationshipsMode GameGhostRelationshipsMode {
            set {
                _ghostRelationshipsMode = value;
                GhostsRelationshipsModeChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        private List<Hero> _heroes = new List<Hero>();
        public List<Hero> Heroes {
            get { return _heroes; }
            private set {
                if (value == null) {
                    throw new ArgumentException("hero list can't be null");
                }
                _heroes = value;
                foreach (Hero h in _heroes) {
                    if (h != null) {
                        h.IntegerPointReached += (sender, args) => InteractThings();
                    }
                }
            }
        }

        public Field<GameObject> StaticGameObjects { get; private set; }

        internal Pacman Pacman { get; private set; }

        private static int PursuitModeTicks => 500;

        public Game() {
            GhostsRelationshipsModeChanged += NotifyGhostsRelationshipsChanged;
        }

        private void NotifyGhostsRelationshipsChanged(object sender, EventArgs eventArgs) {
            if (Heroes == null) {
                return;
            }
            foreach (var hero in Heroes) {
                hero.GhostRelationshipsMode = _ghostRelationshipsMode;
            }
        }

        private void SetupHeroes() {
            var heroes = new List<Hero>();

            StaticGameObjects.Foreach((i, j, gameObject) => {
                var hero = gameObject as Hero;
                if (hero != null) {
                    heroes.Add(hero);
                    var pacman = gameObject as Pacman;
                    if (pacman != null) {
                        Pacman = pacman;
                    }
                }
            });

            StaticGameObjects.Foreach((i, j, gameObject) => {
                var ghost = gameObject as Ghost;
                if (ghost != null) {
                    ghost.Pacman = Pacman;
                }
            });

            Heroes = heroes;
        }

        private int _dotsLeftCount;

        public void SetupGame(Field<char> initialField) {
            if (initialField == null) {
                throw new ArgumentException("initialField can't be null", nameof(initialField));
            }
            StaticGameObjects = new Field<GameObject>(initialField.Width, initialField.Height);

            _dotsLeftCount = 0;
            for (int i = 0; i < initialField.Width; ++i) {
                for (int j = 0; j < initialField.Height; ++j) {
                    StaticGameObjects[i, j] = ProduceGameObject(initialField[i, j], i, j, StaticGameObjects);
                }
            }

            GameStatus = Status.Paused;

            _pursuitModeTimer = new TickTimer(PursuitModeTicks,
                () => { GameGhostRelationshipsMode = GhostRelationshipsMode.GhostsAreEvil; });

            SetupHeroes();
            GameGhostRelationshipsMode = GhostRelationshipsMode.GhostsAreEvil;
        }

        private void MoveHeroes(double milliseconds) {
            if (milliseconds < 0 || Heroes == null) {
                return;
            }
            foreach (var hero in Heroes) {
                hero.Move(milliseconds);                
            }
        } 

        private void InteractThings() {
            if (Heroes == null || StaticGameObjects == null) {
                return;
            }
            foreach (var hero1 in Heroes) {
                foreach (var hero2 in Heroes) {
                    hero1?.InteractWith(hero2);
                }
                if (hero1?.IntPosition != null) {
                    hero1.InteractWith(StaticGameObjects[hero1.IntPosition.Value]);
                    if (hero1.IntPosition != null) { // special for resharper
                        StaticGameObjects[hero1.IntPosition.Value]?.InteractWith(hero1);
                    }
                }                
            }
        }

        private readonly object _stepLock = new object();
        public void Step(double milliseconds) {
            if (milliseconds < 0) {
                throw new ArgumentException("milliseconds can't be negative");
            }
            lock (_stepLock) {
                if (GameStatus == Status.Playing) {
                    MoveHeroes(milliseconds);
                    Tick();
                }
            }
        }
    }
}
