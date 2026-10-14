using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Threading;
using System.Timers;
using System.Windows.Input;
using GameCore;
using Timer = System.Timers.Timer;

namespace Gui.ViewModels {
    internal sealed class GameViewModel : INotifyPropertyChanged, IDisposable {
        public event PropertyChangedEventHandler PropertyChanged;

        private readonly Game _game;

        private HeroesViewModel _heroesViewModel;
        public HeroesViewModel HeroesViewModel {
            get {
                return _heroesViewModel;
            }
            set {
                _heroesViewModel = value;
                OnPropertyChanged(nameof(HeroesViewModel));
            }
        }

        private GameObjectsViewModel _staticGameObjectsViewModel;
        public GameObjectsViewModel StaticGameObjectsViewModel {
            get { return _staticGameObjectsViewModel; }
            set {
                _staticGameObjectsViewModel = value;
                OnPropertyChanged(nameof(StaticGameObjectsViewModel));
            }
        }

        private ICommand WrapGoCommand(ICommand goCommand) {
            return new DelegateCommand(() => {
                _game.TryUnpause();
                goCommand.Execute(null);
            });
        }

        public ICommand PacmanGoLeftCommand
            => WrapGoCommand(HeroesViewModel.PacmanGoLeftCommand);
        public ICommand PacmanGoRightCommand
            => WrapGoCommand(HeroesViewModel.PacmanGoRightCommand);
        public ICommand PacmanGoUpCommand
            => WrapGoCommand(HeroesViewModel.PacmanGoUpCommand);
        public ICommand PacmanGoDownCommand
            => WrapGoCommand(HeroesViewModel.PacmanGoDownCommand);

        private readonly Timer _gameTimer = new Timer();
        private readonly Stopwatch _timerStepStopwatch = Stopwatch.StartNew();
        private readonly object _timerLock = new object();

        private void SetTimerEnabled(bool ena) {
            _gameTimer.Enabled = ena;

            if (ena) {
                _gameTimer.Start();
            }
            lock (_timerLock) {
                _timerStepStopwatch.Reset();
            }
        }

        public GameViewModel(Game game) {
            if (game == null) {
                throw new ArgumentException("game can't be null");
            }
            _game = game;
            var gameObjectsList = new List<GameObject>();
            int fieldW = game.StaticGameObjects.Width;
            int fieldH = game.StaticGameObjects.Height;
            for (int i = 0; i < fieldW; ++i) {
                for (int j = 0; j < fieldH; ++j) {
                    gameObjectsList.Add(game.StaticGameObjects[i,j]);
                }
            }
            
            StaticGameObjectsViewModel = new GameObjectsViewModel(gameObjectsList, fieldW, fieldH);
            HeroesViewModel = new HeroesViewModel(new List<GameObject>(game.Heroes), fieldW, fieldH);

            _timerStepStopwatch.Reset();

            game.GameStatusChanged += (sender, args) => {
                SetTimerEnabled(game.GameStatus == Game.Status.Playing);
            };

            _gameTimer.AutoReset = false;
            _gameTimer.Enabled = true;
            _gameTimer.Elapsed += GameTimerOnElapsed;
            const int timerIntervalMilliseconds = 15;
            _gameTimer.Interval = timerIntervalMilliseconds;
        }

        private void GameTimerOnElapsed(object sender, ElapsedEventArgs elapsedEventArgs) {
            if (Monitor.TryEnter(_timerLock)) {
                try {
                    _timerStepStopwatch.Stop();
                    _game.Step(_timerStepStopwatch.ElapsedMilliseconds);
                    _gameTimer.Stop();
                    _gameTimer.Start();
                    _timerStepStopwatch.Restart();
                } finally {
                    Monitor.Exit(_timerLock);
                }
            }
        }

        public ICommand TogglePause => new DelegateCommand(() => {
            SetTimerEnabled(_gameTimer.Enabled = !_gameTimer.Enabled);
        });

        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void Dispose(bool disposing) {
            if (disposing) {
                if (_gameTimer != null) {
                    _gameTimer.Dispose();
                }
            }
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~GameViewModel() {
            Dispose(false);
        }
    }
}
