using System;

namespace PacMan.Model.Cells
{
    sealed class MegaPillCell : Cell
	{
		internal static readonly Func<Field, int, int, Cell>Creator = (field, x, y) => new MegaPillCell(field, x, y);

		private MegaPillCell(Field field, int x, int y) : base(field, x, y, CellType.Passive)
		{}

	    public override char GetRepresentation()
	    {
	        return CellRepresentations.MegaPillCellRepresentation;
	    }

		internal override bool AbleToMove()
		{
			return true;
		}
	}
}
