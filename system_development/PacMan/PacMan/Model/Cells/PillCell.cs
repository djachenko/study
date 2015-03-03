using System;

namespace PacMan.Model.Cells
{
    sealed class PillCell : Cell
	{
		internal static readonly Func<Field, int, int, Cell>Creator = (field, x, y) => new PillCell(field, x, y);

		private PillCell(Field field, int x, int y) : base(field, x, y, CellType.Passive)
		{}

	    public override char GetRepresentation()
	    {
	        return CellRepresentations.PillCellRepresentation;
	    }

		internal override bool AbleToMove()
		{
			return true;
		}
	}
}
