using System.Collections.Generic;
using System.Linq;

namespace PacMan.Model
{
    public sealed class Direction
    {
        public static readonly Direction Up = new Direction(0, -1, "Up");
        public static readonly Direction Right = new Direction(1, 0, "Right");
        public static readonly Direction Down = new Direction(0, 1, "Down");
        public static readonly Direction Left = new Direction(-1, 0, "Left");
        public static readonly Direction Place = new Direction(0, 0, "Place");

        public static readonly IEnumerable<Direction> Values = new[] { Up, Right, Down, Left };
        private static readonly IEnumerable<Direction> InternalValues = Values.Concat(new[] { Place });

        public int Dx { get; private set; }
        public int Dy { get; private set; }

        public string Name { get; private set; }

        private Direction(int dx, int dy, string name)
        {
            Dx = dx;
            Dy = dy;
            Name = name;
        }

        public override string ToString()
        {
            return base.ToString() + '.' + Name;
        }

        public static Direction Parse(string name)
        {
            return InternalValues.FirstOrDefault(direction => direction.Name.Equals(name));
        }

        public static Direction Parse(int dx, int dy)
        {
            return InternalValues.FirstOrDefault(direction => direction.Dx == dx && direction.Dy == dy);
        }
    }
}
