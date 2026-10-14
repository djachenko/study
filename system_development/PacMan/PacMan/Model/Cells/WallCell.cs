using System;

namespace PacMan.Model.Cells
{
    sealed class WallCell : Cell
	{
	    internal static readonly Func<Field, int, int, Cell> Creator = (field, x, y) => new WallCell(field, x, y);

	    private WallCell(Field field, int x, int y) : base(field, x, y, CellType.Landscape)
	    {
	    }

	    public override char GetRepresentation()
		{
			return CellRepresentations.WallCellRepresentation;
		}

		internal override bool AbleToMove()
		{
			return false;
		}
	}
}
