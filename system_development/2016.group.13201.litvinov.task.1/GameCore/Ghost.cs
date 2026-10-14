using System;
using JetBrains.Annotations;

namespace GameCore {
    public abstract class Ghost : Hero {
        private Pacman _pacman;
        internal Pacman Pacman {
            private get { return _pacman; }
            set {
                // value can be null.
                if (_pacman != null) {
                    throw new ArgumentException("pacman has to be set once");
                }

                _pacman = value;
                if (_pacman.IntPosition != null) {
                    LastPacmanIntPosition = _pacman.IntPosition.Value;
                }
                if (_pacman != null) { 
                    _pacman.IntegerPointReached += (sender, args) => {
                        if (Pacman.IntPosition != null) {
                            LastPacmanIntPosition = Pacman.IntPosition.Value;
                        }
                    };
                }
            }
        }

        private const int EatScore = 100;
        protected PointInt LastPacmanIntPosition { get; private set; }

        private static readonly GhostLoader GhostLoader = new GhostLoader();

        private static readonly IGameObjectLoader Loader
           = new DefaultGameObjectLoader((position, otherObjects) => CreateGhostInFactory(otherObjects,position), '=');

        private static GameObject CreateGhostInFactory(Field<GameObject> staticGameObjects, PointInt initialPosition) {
            try {
                Ghost ghost = GhostLoader.CreateGhost(staticGameObjects, initialPosition);
                return ghost;
            } catch (Exception) {
                throw new GhostCreateException("Неожиданное исключение при создании приведения.");
            }
        }

        [UsedImplicitly]
        public static IGameObjectLoader GetLoader() {
            return Loader;
        }

        protected Ghost(Field<GameObject> staticGameObjects, PointInt initialPosition)
            : base(staticGameObjects, initialPosition) 
        {
            IntegerPointReached += (sender, args) => {
                if (IntPosition != null) {
                    MakeDecisions();
                }
            };
        }

        protected abstract void DecideAsEvil();
        protected abstract void DecideAsFood();

        private int _stayingCounter;
        private const int MaxStaySteps = 20;
        protected override void OnHeroMoveStepHappened() {
            if (!IsMoving) {
                if (++_stayingCounter <= MaxStaySteps) { return; }
                MakeDecisions();
                _stayingCounter = 0;
            } else {
                _stayingCounter = 0;
            }
        }

        private void MakeDecisions() {
            if (GhostRelationshipsMode == GhostRelationshipsMode.GhostsAreEvil) {
                DecideAsEvil();
            } else {
                DecideAsFood();
            }
        }

        internal override void InteractWith(GameObject cause) {
            var pacman = cause as Pacman;
            if (pacman != null) {
                if (IsNear(pacman)) {
                    if (GhostRelationshipsMode == GhostRelationshipsMode.GhostsAreFood) {
                        Respawn();
                        pacman.Score += EatScore;
                    }
                    else {
                        pacman.Die();
                    }
                } 
            }
        }
    }
}
