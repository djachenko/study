using System;
using System.Collections.Generic;
using System.Globalization;
using WpfApplicationPacMan.Annotations;
using WpfApplicationPacMan.Model;
using WpfApplicationPacMan.Model.Champions;
using WpfApplicationPacMan.Model.Ghosts;
using WpfApplicationPacMan.Model.Level;
using WpfApplicationPacMan.ViewModel.Commands;

namespace WpfApplicationPacMan.ViewModel
{
    sealed class MainViewModel : ViewModelBase
    {
        #region fields
        private Game _game;
        private String _currentLevel;
        private String _lives;
        private String _score = "0";
        private MenuCommand _pauseCommand;
        private Position _pacmanPosition;
        private List<Position> _ghostsPositions;
        private List<Position> _pillsPositions;
        private List<Position> _powerPillsPositions;
        private bool _isAttackedModeOn;
        private readonly ChampionsTable _championsTable = new ChampionsTable();
        EventHandler _handler;
        EventHandler _finishHandler;
        
        #endregion fields


        #region properties
        public string Score
        {
            set
            {
                _score = value;
                OnPropertyChanged("Score");
            }
            get
            {
                return _score;
            }
        }
        public string Lives
        {
            get
            {
                return _lives;
            }
            set
            {
                _lives = value;
                OnPropertyChanged("Lives");

            }

        }
        public string CurrentLevelNumber
        {
            get
            {
                return _currentLevel;
            }
            set
            {
                _currentLevel = value;
                OnPropertyChanged("CurrentLevelNumber");
            }

        }

        public MenuCommand UpCommand
        {
            get;
            set;
        }
        public MenuCommand DownCommand
        {
            get;
            set;
        }
        public MenuCommand LeftCommand
        {
            get;
            set;
        }
        public MenuCommand RightCommand
        {
            get;set;
        }
        public MenuCommand PauseCommand
        {
            get { return _pauseCommand; }
            set
            {
                if (value == _pauseCommand) return;
                _pauseCommand = value;
                OnPropertyChanged("PauseCommand");
            }
        }

        public MenuCommand SaveRecordCommand
        {
            get;
            set;
        }
        public List<Position> GhostsPositions
        {
            get
            {
                return _ghostsPositions;
            }
            set
            {
                _ghostsPositions = value;
                OnPropertyChanged("GhostsPositions");
            }
        }
        public List<Position> PillsPositions
        {
            get
            {
                return _pillsPositions;
            }
            set
            {
                _pillsPositions = value;
                OnPropertyChanged("PillsPositions");
            }
        }
        public List<Position> PowerPillsPositions
        {
            get
            {
                return _powerPillsPositions;
            }
            set
            {
                _powerPillsPositions = value;
                OnPropertyChanged("PowerPillsPositions");
            }
        }
        public Position PacmanPosition
        {
            get
            {
                return _pacmanPosition;
            }
            set
            {
                _pacmanPosition = value;
                OnPropertyChanged("PacmanPosition");
            }
        }
        [NotNull]
        public String Name
        {
            get;
            set;
        }
        public int PixelsOnCell
        {
            get;
            set;
        }
       //addd delegating member

        public int FieldHeight
        {
            get { return _game.СurrentLevel.HeightOfField * PixelsOnCell; }
            set
            {
                if (value != _game.СurrentLevel.HeightOfField * PixelsOnCell)
                {
                    OnPropertyChanged("FieldHeight");
                }
            }
        }
        public int FieldWidth
        {
            get { return _game.СurrentLevel.WidthOfField * PixelsOnCell; }
        }

        public SortedList<int, String> ChampionsList
        {
            get;
            set;
        }

        public bool IsAttackedModeOn
        {
            get
            {
                return _isAttackedModeOn;
            }
            set
            {
                _isAttackedModeOn = value;
                OnPropertyChanged("IsAttackedModeOn");
            }
        }
        #endregion
         
        
        public MainViewModel()
        {
            UpCommand = new MenuCommand(ChangePlayerDirectionToUp);
            DownCommand = new MenuCommand(ChangePlayerDirectionToDown);
            LeftCommand = new MenuCommand(ChangePlayerDirectionToLeft);
            RightCommand = new MenuCommand(ChangePlayerDirectionToRight);
            PauseCommand = new MenuCommand(Pause);
            SaveRecordCommand = new MenuCommand(SaveRecord);
            PixelsOnCell = 30;
            Name = "unknown";
            Lives = "2";
            CurrentLevelNumber = "1";
            _game = new Game(PacmanPositionChangedHandler, GhostsPositionsChangedHandler,
                PillsChangesHandler, LivesChangesHandler, PowerPillsChangesHandler);
            PillsPositions = _game.СurrentLevel.PillsPositions;
            PowerPillsPositions = _game.СurrentLevel.PowerPillsPositions;
            ChampionsList = _championsTable.Dictionary;
        }

        
        public bool IsNewRecordsman()
        {
            return _championsTable.IsNewRecordsman(_game.Player.Score);
        }

        private void SaveRecord(object obj)
        {
            _championsTable.Add(Name, _game.Player.Score);
        }

        #region methods for commands
        public void Pause(object obj)
        {
            _game.Stop();
        }

        private void ChangePlayerDirectionToRight(object obj)
        {
            _game.Player.PlayerDirection = Player.Direction.Right;
            if (!_game.IsStarted)
            {
                _game.Start();
            }
        }

        private void ChangePlayerDirectionToLeft(object obj)
        {
            _game.Player.PlayerDirection = Player.Direction.Left;
            if (!_game.IsStarted)
            {
                _game.Start();
            }
        }

        private void ChangePlayerDirectionToDown(object obj)
        {
            _game.Player.PlayerDirection = Player.Direction.Down;
            if (!_game.IsStarted)
            {
                _game.Start();
            }
        }

        private void ChangePlayerDirectionToUp(object obj)
        {
            _game.Player.PlayerDirection = Player.Direction.Up;
            if (!_game.IsStarted)
            {
                _game.Start();
            }
        }
        #endregion methods for commands

        private void PillsChangesHandler(object sender, EventArgs eventArgs)
        {
            PillsPositions = ((PositionsEventArgs)eventArgs).Positions;
            Score = _game.Player.Score.ToString(CultureInfo.InvariantCulture);
        }
        private void PowerPillsChangesHandler(object sender, EventArgs eventArgs)
        {
            PowerPillsPositions = ((PositionsEventArgs)eventArgs).Positions;
        }

        private void LivesChangesHandler(object sender, EventArgs eventArgs)
        {
            Lives = ((LivesNumbersEventArgs)eventArgs).Lives.ToString(CultureInfo.InvariantCulture);
        }
        private void CurrentLevelNumberChangesHandler(object sender, EventArgs eventArgs)
        {
            CurrentLevelNumber = ((CurrentLevelNumberEventArgs)eventArgs).Number.ToString(CultureInfo.InvariantCulture);
        }

        private void PacmanPositionChangedHandler(object sender, EventArgs eventArgs)
        {
            PacmanPosition = ((Player.PositionEventArgs)eventArgs).Position;
        }

        private void GhostsPositionsChangedHandler(object sender, EventArgs eventArgs)
        {
            GhostsPositions = ((PositionsEventArgs) eventArgs).Positions;
            Score = _game.Player.Score.ToString(CultureInfo.InvariantCulture);
            IsAttackedModeOn = ((PositionsEventArgs)eventArgs).IsAttackedModeOn;
        }


        public void GameFinishedHandler(EventHandler handler)
        {
            _finishHandler = handler;
            _game.GameFinished += handler;
        }

        public void NewLevelLoadedHandler(EventHandler handler)
        {
            _handler = handler;
            _game.NewLevelLoaded += handler;
            _game.NewLevelLoaded += CurrentLevelNumberChangesHandler;
            _game.Init();
            //handler(null,null);
        }

        public void Start()
        {
            _game.Start();
        }

        public List<Position> GetListWalls()
        {
            return _game.СurrentLevel.WallsPositions;
        }

        public void NewGame()
        {
            _game.Stop();
            _game = new Game(PacmanPositionChangedHandler, GhostsPositionsChangedHandler,
                PillsChangesHandler, LivesChangesHandler, PowerPillsChangesHandler);
            _game.NewLevelLoaded += _handler;
            _game.GameFinished += _finishHandler;
            _game.Init();
//            _handler(null,null);
            PillsPositions = _game.СurrentLevel.PillsPositions;
            PowerPillsPositions = _game.СurrentLevel.PowerPillsPositions;
            GhostsPositions = _game.СurrentLevel.GhostsPositions;
            ChampionsList = _championsTable.Dictionary;
            Score = _game.Player.Score.ToString(CultureInfo.InvariantCulture);
            Lives = _game.Player.Lives.ToString(CultureInfo.InvariantCulture);
            CurrentLevelNumber = "1";
        }
    }
}
