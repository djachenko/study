using System.Collections.Generic;

namespace PacMan.Model.Cells
{
    public sealed class CellType
    {
        public static readonly CellType Active = new CellType(0, "active");
        public static readonly CellType Passive = new CellType(1, "passive");
        public static readonly CellType Landscape = new CellType(2, "land");

        public static readonly IEnumerable<CellType> Values = new[] { Active, Passive, Landscape };

        public int Order { get; private set; }
        private readonly string _name;

        private CellType(int order, string name)
        {
            Order = order;
            _name = name;
        }

        public override string ToString()
        {
            return _name;
        }
    }
}
