using System;

namespace PacMan.Model.Cells
{
    sealed class SpaceCell : Cell
	{
	    internal static readonly Func<Field, int, int, Cell> Creator = (field, x, y) => new SpaceCell(field, x, y);

	    private SpaceCell(Field field, int x, int y) : base(field, x, y, CellType.Landscape)
	    {
	    }

	    public override char GetRepresentation()
	    {
	        return CellRepresentations.SpaceCellRepresentation;
	    }

		internal override bool AbleToMove()
		{
			return true;
		}
	}
}
