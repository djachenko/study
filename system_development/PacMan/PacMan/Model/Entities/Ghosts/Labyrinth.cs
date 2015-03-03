using System;
using System.Collections.Generic;

namespace PacMan.Model.Entities.Ghosts
{
    sealed class Point
    {
        public int X { get; set; }
        public int Y { get; set; }
    }

    sealed class Labyrinth
    {
        private const int DefaultWayValue = int.MaxValue;

        private bool[,] PassMask { get; set; }
        private int[,] Way { get; set; }

        public Labyrinth(bool[,] passMask)
        {
            PassMask = passMask;

            Way = new int[passMask.GetLength(0), passMask.GetLength(1)];
        }

        internal Direction GetNextDirection(int fromX, int fromY, int toX, int toY)
        {
            ValidateCoordinates(ref fromX, ref fromY);
            ValidateCoordinates(ref toX, ref toY);

            FindNearestSpace(ref toX, ref toY);

            BuildWay(fromX, fromY, toX, toY);
            var direction = TraceBack(toX, toY);

            return direction;
        }

        private void ValidateCoordinates(ref int x, ref int y)
        {
            if (x < 1)
            {
                x = 1;
            }

            if (x > PassMask.GetLength(0) - 2)
            {
                x = PassMask.GetLength(0) - 2;
            }

            if (y < 1)
            {
                y = 1;
            }

            if (y > PassMask.GetLength(1) - 2)
            {
                y = PassMask.GetLength(1) - 2;
            }
        }

        private void FindNearestSpace(ref int x, ref int y)
        {
            ClearWay();

            var points = new Queue<Point>();
            points.Enqueue(new Point { X = x, Y = y });

            Way[x, y] = 0;

            while (true)
            {
                var point = points.Dequeue();

                if (PassMask[point.X, point.Y])
                {
                    x = point.X;
                    y = point.Y;

                    return;
                }

                for (var dx = -1; dx <= 1; dx++)
                {
                    for (var dy = Math.Abs(dx) - 1; dy <= 1 - Math.Abs(dx); dy += 2)
                    {
                        var newX = point.X + dx;
                        var newY = point.Y + dy;

                        if (newX >= 1 && 
                            newX < PassMask.GetLength(0) - 1 && 
                            newY >= 1 && 
                            newY < PassMask.GetLength(1) - 1 &&
                            Way[newX, newY] > Way[point.X, point.Y] + 1)
                        {
                            Way[newX, newY] = Way[point.X, point.Y] + 1;
                            points.Enqueue(new Point { X = newX, Y = newY });
                        }
                    }
                }

                //PrintWay();
            }
        }

        private void BuildWay(int fromX, int fromY, int toX, int toY)
        {
            ClearWay();

            var points = new Queue<Point>();
            points.Enqueue(new Point { X = fromX, Y = fromY });

            Way[fromX, fromY] = 0;

            while (true)
            {
                var point = points.Dequeue();

                if (point.X == toX && point.Y == toY)
                {
                    break;
                }

                for (var dx = -1; dx <= 1; dx++)
                {
                    for (var dy = Math.Abs(dx) - 1; dy <= 1 - Math.Abs(dx); dy += 2)
                    {
                        var newPoint = new Point { X = point.X + dx, Y = point.Y + dy };

                        if (PassMask[newPoint.X, newPoint.Y] && 
                            Way[newPoint.X, newPoint.Y] > Way[point.X, point.Y] + 1)
                        {
                            Way[newPoint.X, newPoint.Y] = Way[point.X, point.Y] + 1;
                            points.Enqueue(newPoint);
                        }
                    }
                }

                //PrintWay();
            }
        }

        private Direction TraceBack(int fromX, int fromY)
        {
            var point = new Point { X = fromX, Y = fromY };

            while (Way[point.X, point.Y] > 1)
            {
                var flag = false;

                for (var dx = -1; !flag && dx <= 1; dx++)
                {
                    for (var dy = Math.Abs(dx) - 1; !flag && dy <= 1 - Math.Abs(dx); dy += 2)
                    {
                        var newPoint = new Point { X = point.X + dx, Y = point.Y + dy };

                        if (Way[newPoint.X, newPoint.Y] == Way[point.X, point.Y] - 1)
                        {
                            point = newPoint;

                            flag = true;
                        }
                    }
                }
            }

            for (var dx = -1; dx <= 1; dx++)
            {
                for (var dy = Math.Abs(dx) - 1; dy <= 1 - Math.Abs(dx); dy += 2)
                {
                    var newPoint = new Point { X = point.X + dx, Y = point.Y + dy };

                    if (Way[newPoint.X, newPoint.Y] == 0)
                    {
                        var direction = Direction.Parse(-dx, -dy);

                        return direction;
                    }
                }
            }

            return Direction.Parse(0, 0);
        }

        void ClearWay()
        {
            for (var x = 0; x < Way.GetLength(0); x++)
            {
                for (var y = 0; y < Way.GetLength(1); y++)
                {
                    Way[x, y] = DefaultWayValue;
                }
            }
        }
    }
}
