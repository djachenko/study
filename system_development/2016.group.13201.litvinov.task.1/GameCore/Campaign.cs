using System;
using System.Collections.Generic;
using System.Linq;

namespace GameCore {
    public sealed class Campaign : IDisposable {
        private List<Game> GamesList { get; set; }

        private Game _activeGame;
        public event EventHandler ActiveGameChanged;
        public event EventHandler ScoreChanged;
        public event EventHandler OnWin;
        public event EventHandler OnGameover;
        public event EventHandler LivesChanged;

        private void UnsubscribeActiveGame() {
            if (ActiveGame == null) {
                return;
            }
            ActiveGame.GameStatusChanged -= OnGameStatusChanged;
            ActiveGame.ScoreChanged -= OnGameScoreChanged;
           ActiveGame.Pacman.LivesChanged -= OnLivesChanged;
        }

        private void OnGameStatusChanged(object sender, EventArgs args) {
            if (ActiveGame.GameStatus == Game.Status.Win) {
                if (!ActivateNextGame()) {
                    OnWin?.Invoke(this, EventArgs.Empty);
                }
            }
            if (ActiveGame.GameStatus == Game.Status.GameOver) {
                OnGameover?.Invoke(this, EventArgs.Empty);
            }
        }

        private void OnGameScoreChanged(object sender, EventArgs args) {
            ScoreChanged?.Invoke(this, EventArgs.Empty);
        }

        private void OnLivesChanged(object sender, EventArgs args) {
            LivesChanged?.Invoke(this, EventArgs.Empty);
        }

        private void SubscribeActiveGame() {
            ActiveGame.GameStatusChanged += OnGameStatusChanged;
            ActiveGame.ScoreChanged += OnGameScoreChanged;
            ActiveGame.Pacman.LivesChanged += OnLivesChanged;
        }

        private List<Game>.Enumerator _activeGameEnumerator;
        public Game ActiveGame {
            get { return _activeGame; }
            private set {
                if (value == null) {
                    throw new ArgumentException("activeGame can't be null");
                }
                _lives = _activeGame?.Pacman.Lives ?? InitialLives; 
                UnsubscribeActiveGame();    
                _activeGame = value;
                SubscribeActiveGame();
                _activeGame.Pacman.Lives = _lives;
                ActiveGameChanged?.Invoke(this, EventArgs.Empty);
            }
        }

        private const int InitialLives = 5;

        public int Score => GamesList.Sum(game => game.Score);

        private int _lives = InitialLives;
        public int Lives => ActiveGame.Pacman.Lives;

        private bool ActivateNextGame() {
            bool isActivated = _activeGameEnumerator.MoveNext();
            if (isActivated) {
                ActiveGame = _activeGameEnumerator.Current;
            }
            return isActivated;
        }

        private void Init(List<Game> gamesList) {
            if (gamesList == null || gamesList.Count == 0) {
                throw new ArgumentException("gamesList can't be null or empty");
            }
            GamesList = gamesList;
            _activeGameEnumerator = GamesList.GetEnumerator();
        }

        public Campaign(List<Game> gamesList) {
            if (gamesList == null || gamesList.Count == 0) {
                throw new ArgumentException("gamesList can't be null or empty");
            }
            Init(gamesList);
        }

        public void Start() {
            ActivateNextGame();
        }

        public void Dispose() {
            _activeGameEnumerator.Dispose();
        }
    }
}
