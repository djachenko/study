using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading;
using WpfApplicationPacMan.Model.Ghosts;

namespace WpfApplicationPacMan.Model.Level
{
    internal sealed class Level
    {
        #region events
        public EventHandler ChangesHandler;
        public EventHandler PillsChangesHandler;
        public EventHandler PowerPillsChangesHandler;
        #endregion events
        
        #region fields
        private readonly Player _player;
        private readonly Field _field;
        private readonly List<Ghost> _ghosts = new List<Ghost>();
        private readonly GhostsFactory _ghostsFactory;
        #endregion fields

        #region properties
        public List<Position> PowerPillsPositions
        {
            get
            {
                return _field.PowerPillsPositions;
            }
        }
        public List<Position> PillsPositions
        {
            get { return _field.PillsPositions; }
        }
        public int HeightOfField
        {
            get
            {
                return _field.HeightOfField;
            }
        }
        public int WidthOfField
        {
            get { return _field.WidthOfField; }
        }
        public int LevelNumber
        {
            get;
            private set;
        }
        public bool IsFinished
        {
            get;
            private set;
        }
        public bool IsWon
        {
            get;
            private set;
        }
        public bool IsRestart
        {
            get;
            private set;
        }
        public List<Position> WallsPositions
        {
            get
            {
                return _field.WallsPositions;
            }
        }
        public List<Position> GhostsPositions
        {
            get { return _ghosts.Select(ghost => ghost.Position).ToList(); }
        }



        #endregion properties


        public Level(int levelNumber, string pathToMap, Player player, GhostsFactory ghostsFactory)
        {
            #region null cheking
            if (null == pathToMap)
            {
                throw new ArgumentNullException("pathToMap");
            }
            if (null == player)
            {
                throw new ArgumentNullException("player");
            }
            if (null == ghostsFactory)
            {
                throw new ArgumentNullException("ghostsFactory");
            }
            #endregion null cheking

            _field = new Field(pathToMap);
            _ghostsFactory = ghostsFactory;
            LevelNumber = levelNumber;
            _player = player;
            _player.Position = _field.PlayerStartPosition;

            InitGhosts();
        }

        #region notifiers
        private void NotifyAboutGhostsPositionsChanges()
        {
            var temp = Volatile.Read(ref ChangesHandler);
            if (temp != null)
            {
                temp(this, new PositionsEventArgs { Positions = GhostsPositions, IsAttackedModeOn = _ghosts.First().IsAttackModeOn });
            }
        }
        private void NotifyAboutPillsChanges()
        {
            var temp = Volatile.Read(ref PillsChangesHandler);
            if (temp != null)
            {
                temp(this, new PositionsEventArgs { Positions = _field.PillsPositions });
            }
        }
        private void NotifyAboutPowerPillsChanges()
        {
            var temp = Volatile.Read(ref PowerPillsChangesHandler);
            if (temp != null)
            {
                temp(this, new PositionsEventArgs { Positions = _field.PowerPillsPositions });
            }
        }
        #endregion notifiers


        /// <summary>
        /// отключить у призраков режим нападения
        /// </summary>
        private void OffAttackedMode()
        {
            foreach (var ghost in _ghosts)
            {
                ghost.IsAttackModeOn = false;
            }
        }


        /// <summary>
        /// вычислить количество призраков, создать их и установить стартовые позиции призраков
        /// </summary>
        private void InitGhosts()
        {
            _ghosts.Clear();
            var ghostsStartPositions = _field.GhostRespawnPositions.GetEnumerator();

            for (var i = 0; i < _field.GetNumberOfGhosts(); i++)
            {
                ghostsStartPositions.MoveNext();
                _ghosts.Add(_ghostsFactory.GetGhost(ghostsStartPositions.Current, _field.GetMatrix()));

            }
            NotifyAboutGhostsPositionsChanges();
        }



        /// <summary> 
        /// игровой цикл.
        /// проверка на конец уровня
        ///делают ход пакмэн и призраки
        /// </summary>
        [MethodImpl(MethodImplOptions.Synchronized)]
        public void Proceed()
        {
            if (IsRestart)
            {
                return;
            }
            if (_field.PillsPositions.Count == 0)
            {
                IsFinished = true;
                IsWon = true;
                return;
            }

            if (CheckClash())
            {
                return;
            }

            if (_field.IsTheWayFree(_player.Position, _player.PlayerDirection))
            {
                _player.Move();
                CheckPills();
                CheckPowerPills();
            }

            if (!IsRestart)
            {
                if (CheckClash())
                {
                    return;
                }
            }

            foreach (var ghost in _ghosts)
            {
                ghost.Move(_player.Position);
                NotifyAboutGhostsPositionsChanges();
            }
        }

        /// <summary>
        /// check meeting pacman and ghosts
        /// </summary>
        /// <returns></returns>
        private bool CheckClash()
        {
            foreach (var ghost in _ghosts)
            {
                if (_player.Position.CoordinateX == ghost.Position.CoordinateX
                    && _player.Position.CoordinateY == ghost.Position.CoordinateY)
                {
                    if (ghost.IsAttackModeOn)
                    {
                        _player.Lives--;
                        if (_player.Lives <= 0)
                        {
                            IsFinished = true;
                            IsWon = false;
                        }
                        IsRestart = true;
                        NotifyAboutGhostsPositionsChanges();
                        return true;
                    }
                    _player.Score += 10;
                    ghost.Position = _field.GhostRespawnPositions.First();//!!!!!!!!!!!!!!!!
                    NotifyAboutGhostsPositionsChanges();
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// check meeting pacman and powerpill
        /// </summary>
        private void CheckPowerPills()
        {
            var c = _field.PowerPillsPositions.Find(FindPillsPredicat);
            if (_field.PowerPillsPositions.Contains(c))
            {
                _field.PowerPillsPositions.Remove(c);
                OffAttackedMode();
                NotifyAboutPowerPillsChanges();
            }
        }

        //TODO: выяснять какая пилюля исчезла и только при обновлении удалять только ее
        /// <summary>
        /// check meeting pacman and pill
        /// </summary>
        private void CheckPills()
        {
            var c = _field.PillsPositions.Find(FindPillsPredicat);
            if (_field.PillsPositions.Contains(c))
            {
                _field.PillsPositions.Remove(c);
                _player.Score++;
                NotifyAboutPillsChanges();
            }
        }

        private bool FindPillsPredicat(Position obj)
        {
            return obj.CoordinateX == _player.Position.CoordinateX && obj.CoordinateY == _player.Position.CoordinateY;
        }

        public void Init()
        {
            NotifyAboutPillsChanges();
            NotifyAboutGhostsPositionsChanges();
            NotifyAboutPowerPillsChanges();
        }

        public void Restart()
        {
            _player.Position = _field.PlayerStartPosition;
            InitGhosts();
            IsRestart = false;
        }

        public void UpdatePillsPositions()
        {
            NotifyAboutPillsChanges();
        }
    }
}
