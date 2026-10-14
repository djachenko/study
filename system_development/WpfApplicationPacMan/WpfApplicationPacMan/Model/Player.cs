using System;
using System.Threading;
using WpfApplicationPacMan.Model.Level;

namespace WpfApplicationPacMan.Model
{
    public sealed class Player
    {
        public EventHandler ChangesHandler;
        public EventHandler LivesHandler;
        
        private const int Speed = 1;
        private Position _position;
        private int _lives;

        #region properties
        public Position Position
        {
            get
            {
                return _position;
            }
            set
            {
                _position = value;
                NotifyAboutPositionChanges();
            }
        }
        public int Lives
        {
            get
            {
                return _lives;
            }
            set
            {
                _lives = value;
                NotifyAboutLivesChandes();
            }
        }
        public int Score
        {
            get;
            set;
        }
        public Direction PlayerDirection
        {
            get;
            set;
        }
        #endregion

        public Player(int lives)
        {
            Lives = lives;
        }

        private void NotifyAboutPositionChanges()
        {
            EventHandler temp = Volatile.Read(ref ChangesHandler);
            if (temp != null)
            {
                temp(this, new PositionEventArgs{Position = Position});
            }
        }
        private void NotifyAboutLivesChandes()
        {
            EventHandler temp = Volatile.Read(ref LivesHandler);
            if (temp != null)
            {
                temp(this, new LivesNumbersEventArgs{ Lives = Lives});
            }
        }

        public class PositionEventArgs : EventArgs
        {
            public Position Position
            {
                get;
                set;
            }
             
        }

        public enum Direction
        {
            Up,
            Down,
            Left,
            Right
        };

        public void Move()
        {
            switch (PlayerDirection)
            {
                case Direction.Down:
                    Position.CoordinateY += Speed;
                    break;
                case Direction.Up:
                    Position.CoordinateY -= Speed;
                    break;
                case Direction.Left:
                    Position.CoordinateX -= Speed;
                    break;
                case Direction.Right:
                    Position.CoordinateX += Speed;
                    break;
            }
            NotifyAboutPositionChanges();
        }
    }
}
