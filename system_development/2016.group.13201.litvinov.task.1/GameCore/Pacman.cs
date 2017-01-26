using System;
using JetBrains.Annotations;

namespace GameCore {
    public sealed class Pacman : Hero {
        public event EventHandler DieEvent;
        public event EventHandler LivesChanged;
        public event EventHandler ScoreChanged;
        public event EventHandler EnergizerEatEvent;

        private int _score;

        internal int Score {
            get { return _score; }
            set {
                _score = value > 0 ? value : 0;
                ScoreChanged?.Invoke(this, EventArgs.Empty);
            }
        }
        
        private int _lives;

        internal int Lives {
            get { return _lives; }
            set {
                _lives = value > 0 ? value : 0;
                LivesChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        private const int InitialLives = 5;

        private static readonly IGameObjectLoader Loader
            = new DefaultGameObjectLoader((position, otherObjects) => new Pacman(otherObjects,position), '\\');

        [UsedImplicitly]
        public static IGameObjectLoader GetLoader() {
            return Loader;
        }

        private Pacman(Field<GameObject> staticGameObjects, PointInt initialPosition)
            : base(staticGameObjects, initialPosition) 
        {
            Name = "pacman";
            Lives = InitialLives;
        }

        internal void Die() {
            Lives = Lives - 1;
            DieEvent?.Invoke(this, EventArgs.Empty);
        }

        internal override void InteractWith(GameObject cause) {
            var food = cause as RegularFood;
            if (food != null) {
                if (!food.IsAnnihilated) {
                    if (food is EnergizerGameObject) {
                        EnergizerEatEvent?.Invoke(this, EventArgs.Empty);
                    }
                    Score += food.EatScore;
                    food.Annihilate();
                }
            }
        }
    }
}
