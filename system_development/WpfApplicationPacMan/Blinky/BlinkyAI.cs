using System;
using WpfApplicationPacMan.Annotations;
using WpfApplicationPacMan.Model;
using WpfApplicationPacMan.Model.Ghosts;

namespace Blinky
{
// ReSharper disable InconsistentNaming
    [UsedImplicitly]
    public sealed class BlinkyAI : GhostAI
// ReSharper restore InconsistentNaming
    {
        private const int Speed = 2;
        private int _counter;
        private readonly Random _random = new Random();
        private readonly Array _values = Enum.GetValues(typeof(Player.Direction));

        Player.Direction Direction
        {
            get;
            set;
        }


        public override Position GetNextPosition(Position position, Position playerPosition)
        {
            _counter++;
            _counter %= Speed + 1;
            if (_counter != Speed)
            {
                return position;
            }

            var nextPosition = new Position();
            bool isWayFree;
            do
            {
                
                Direction = (Player.Direction)_values.GetValue(_random.Next(_values.Length));
                isWayFree = IsTheWayFree(position, Direction);
            }
            while (!isWayFree);
            
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

    }
}
