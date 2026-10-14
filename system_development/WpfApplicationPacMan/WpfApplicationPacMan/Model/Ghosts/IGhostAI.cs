using System;
using System.Timers;

namespace WpfApplicationPacMan.Model.Ghosts
{
    public abstract class GhostAI
    {
        private bool _mode;
        private readonly Timer _timer = new Timer(5000);
        protected int[,] Matrix;

        protected GhostAI()
        {
            IsAttackModeOn = true;
            _timer.Elapsed += Tick;
        }

        private void Tick(object sender, ElapsedEventArgs e)
        {
            IsAttackModeOn = true;
            _timer.Stop();
        }
        
        protected bool IsTheWayFree(Position position, Player.Direction direction)
        {
            if (position == null)
            {
                throw new ArgumentNullException("position");
            }

            switch (direction)
            {
                case Player.Direction.Down:
                    return Matrix[position.CoordinateY + 1, position.CoordinateX] != (int)Level.Matrix.Wall;
                case Player.Direction.Up:
                    return Matrix[position.CoordinateY - 1, position.CoordinateX] != (int)Level.Matrix.Wall;
                case Player.Direction.Right:
                    return Matrix[position.CoordinateY, position.CoordinateX + 1] != (int)Level.Matrix.Wall;
                case Player.Direction.Left:
                    return Matrix[position.CoordinateY, position.CoordinateX - 1] != (int)Level.Matrix.Wall;
            }
            return true;
        }


        public bool IsAttackModeOn
        {
            get
            {
                return _mode;
            }
            set
            {
                _mode = value;
                if (!value)
                {
                    _timer.Start();
                }
            }
        }

        abstract public Position GetNextPosition(Position position, Position playerPosition);

        public void SetMatrix(int[,] matrix)
        {
            Matrix = matrix;
        }
    }
}
