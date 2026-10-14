using System;
using System.Threading;
using WpfApplicationPacMan.Model.Level;

namespace WpfApplicationPacMan.Model
{
    sealed class Game
    {
        private readonly Ticker _ticker;
        private readonly LevelsLoader _levelsLoader;
        private bool _finishCatched;
        public event EventHandler NewLevelLoaded;
        public event EventHandler GameFinished;

        #region properties
        public Player Player
        {
            get;
            private set;
        }

        public Level.Level СurrentLevel
        {
            get;
            private set;
        }

        public bool IsStarted
        {
            get;
            private set;
        }

        private void OnGameFinished()
        {
            var handler = GameFinished;
            if (handler != null) handler(this, new PlayerEventArgs {Score = Player.Score});
        }
        #endregion properties

        public Game(EventHandler pacmanHandler, EventHandler ghostsEventHandler, EventHandler pillsEventHandler, EventHandler livesEventHandler, EventHandler powerPillsEventHandler)
        {
            Player = new Player(lives:2);
            Player.ChangesHandler += pacmanHandler;
            Player.LivesHandler += livesEventHandler;

            _levelsLoader = new LevelsLoader(Player, ghostsEventHandler, pillsEventHandler, powerPillsEventHandler);
            СurrentLevel = _levelsLoader.GetNextLevel();
            _ticker = new Ticker(TickAction);
        }

        /// <summary>
        /// Игровой цикл, выполняются действия при очередном ходе
        /// </summary>
        private void TickAction()
        {
            if (СurrentLevel == null || _finishCatched)
            {
                return;
            }
            if (СurrentLevel.IsRestart)
            {
                Stop();
                СurrentLevel.Restart();
                if (СurrentLevel.IsFinished)
                {
                    FinishGame();
                }
                return;
            }

            if (СurrentLevel.IsFinished)
            {
                if (СurrentLevel.IsWon)
                {
                    СurrentLevel = _levelsLoader.GetNextLevel();
                    if (СurrentLevel == null)
                    {
                        FinishGame();
                        return;
                    }
                    Pause();
                    NotifyAboutNewLevel();
                    СurrentLevel.Init();
                    return;
                }
                FinishGame();
                return;
            }
            СurrentLevel.Proceed();
        }

        private void NotifyAboutNewLevel()
        {
            СurrentLevel.UpdatePillsPositions();
            var temp = Volatile.Read(ref NewLevelLoaded);
            if (temp != null)
            {
                temp(this, new CurrentLevelNumberEventArgs { Number = СurrentLevel.LevelNumber });
            }

        }


        #region start, stop, pause, finish game

        private void FinishGame()
        {
            _finishCatched = true;
            Stop();
            OnGameFinished();
        }

        public void Start()
        {
            IsStarted = true;
            _ticker.Start();
        }
        public void Stop()
        {
            //            MessageBox.Show("STOPED");
            IsStarted = false;
            _ticker.Stop();
        }
        public void Pause()
        {
            IsStarted = false;
            _ticker.Stop();
        }

        #endregion

        public void Init()
        {
            СurrentLevel.Init();
            NotifyAboutNewLevel();
        }
    }
}
