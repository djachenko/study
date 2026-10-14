using System;
using WpfApplicationPacMan.Annotations;
using WpfApplicationPacMan.Model;
using WpfApplicationPacMan.Model.Ghosts;

namespace Inly
{
    [UsedImplicitly]
    public sealed class InkyAI : GhostAI
    {
        private const int Speed = 2;
        private int _counter;
        private readonly Random _random = new Random();
        private int _counterForDeadLock;

        private Player.Direction Direction
        {
            get;
            set;
        }

        public InkyAI()
        {
            IsAttackModeOn = true;
        }

        public override Position GetNextPosition(Position position, Position playerPosition)
        {
            CalculateRoute(position, playerPosition);
            _counter++;
            _counter %= Speed + 1;
            if (_counter != Speed)
            {
                return position;
            }

            var nextPosition = new Position();

            #region if stalker mode off
            if (!IsAttackModeOn)
            {
                var otherDirection = Player.Direction.Down;
                do
                {
                    switch (_random.Next(1, 5))
                    {
                        case 1:
                            otherDirection = Player.Direction.Down;
                            break;
                        case 2:
                            otherDirection = Player.Direction.Left;
                            break;
                        case 3:
                            otherDirection = Player.Direction.Right;
                            break;
                        case 4:
                            otherDirection = Player.Direction.Up;
                            break;
                    }
                    _counterForDeadLock++;
                    if (_counterForDeadLock == 3)
                    {
                        _counterForDeadLock = 0;
                        return position;
                    }
                }
                while (!IsTheWayFree(position, otherDirection) || otherDirection == Direction);
                
                Direction = otherDirection;
            }
            #endregion if stalker mode off


            switch (Direction)
            {
                case Player.Direction.Down:
                    nextPosition.CoordinateX = position.CoordinateX;
                    nextPosition.CoordinateY = position.CoordinateY + 1;

                    break;
                case Player.Direction.Left:
                    nextPosition.CoordinateX = position.CoordinateX - 1;
                    nextPosition.CoordinateY = position.CoordinateY;

                    break;
                case Player.Direction.Right:
                    nextPosition.CoordinateX = position.CoordinateX + 1;
                    nextPosition.CoordinateY = position.CoordinateY;
                    break;
                case Player.Direction.Up:
                    nextPosition.CoordinateX = position.CoordinateX;
                    nextPosition.CoordinateY = position.CoordinateY - 1;
                    break;
            }
            return nextPosition;
        }

        /// <summary>
        /// caclulate shortcut to pacman and set the ghost direction
        /// </summary>
        /// <param name="position"></param>
        /// <param name="playerPosition"></param>
        private void CalculateRoute(Position position, Position playerPosition)
        {
            int[,] matrix = new int[Matrix.GetLength(0), Matrix.GetLength(1)];
            for (int i = 0; i < Matrix.GetLength(0); i++)
            {
                for (int j = 0; j < Matrix.GetLength(1); j++)
                {
                    matrix[i, j] = Matrix[i, j];

                }
            }

            int[] dx = {1, 0, -1, 0};
            int[] dy = {0, 1, 0, -1};
            var d = 0;
            bool stop;
            matrix[position.CoordinateY, position.CoordinateX] = 0;

            do
            {
                stop = true; 
                for (var y = 0; y < matrix.GetLength(0)-1; ++y)
                {
                    for (var x = 0; x < matrix.GetLength(1); ++x)
                    {
                        if (matrix[y, x] == d)
                        {
                            for (var k = 0; k < 4; ++k)
                                if (y + dy[k] >= 0 && x + dx[k] >= 0 && y + dy[k] <= matrix.GetLength(0)-1 && x + dx[k] <= matrix.GetLength(1)-1)
                                {
                                    if (matrix[y + dy[k], x + dx[k]] == (int)WpfApplicationPacMan.Model.Level.Matrix.Space 
                                        || 1 != Math.Abs(matrix[y + dy[k], x + dx[k]] - matrix[y, x]) && matrix[y + dy[k], x + dx[k]] != (int) WpfApplicationPacMan.Model.Level.Matrix.Wall)
                                    {
                                        stop = false;
                                        matrix[y + dy[k], x + dx[k]] = d + 1; 
                                    }
                                }
                        }
                    }
                }
                d++;
            }
            while (!stop && matrix[playerPosition.CoordinateY, playerPosition.CoordinateX] == -1);

            // восстановление пути
            var pacmanPositionX = playerPosition.CoordinateX;
            var pacmanPositionY = playerPosition.CoordinateY;
            var px = new int[matrix.GetLength(1) * matrix.GetLength(0)];
            var py = new int[matrix.GetLength(1) * matrix.GetLength(0)];
            var len = matrix[pacmanPositionY, pacmanPositionX];
            d = len;
            while (d > 0)
            {
                px[d] = pacmanPositionX;
                py[d] = pacmanPositionY;
                d--;
                for ( var k = 0; k < 4; ++k)
                    if (pacmanPositionY + dy[k] >= 0 && pacmanPositionX + dx[k] >= 0 && pacmanPositionY + dy[k] <= matrix.GetLength(0) &&
                        pacmanPositionX + dx[k] <= matrix.GetLength(1) - 1)
                    {
                        if (matrix[pacmanPositionY + dy[k], pacmanPositionX + dx[k]] == d)
                        {
                            pacmanPositionX = pacmanPositionX + dx[k];
                            pacmanPositionY = pacmanPositionY + dy[k];
                            break;
                        }
                    }
            }
            px[0] = position.CoordinateX;
            py[0] = position.CoordinateY;

            if (px[1] == px[0] && py[1] == py[0] + 1)
            {
                Direction = Player.Direction.Down;
            }
            if (px[1] == px[0] && py[1] == py[0] - 1)
            {
                Direction = Player.Direction.Up;
            }
            if (px[1] == px[0] +1 && py[1] == py[0])
            {
                Direction = Player.Direction.Right;
            }
            if (px[1] == px[0] - 1 && py[1] == py[0])
            {
                Direction = Player.Direction.Left;
            }
        }
    }

}
