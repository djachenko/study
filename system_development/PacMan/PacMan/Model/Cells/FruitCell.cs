using System;

namespace PacMan.Model.Cells
{
    sealed class FruitCell : Cell
	{
		internal static readonly Func<Field, int, int, Cell>Creator = (field, x, y) => new FruitCell(field, x, y);
		
		private FruitCell(Field field, int x, int y) : base(field, x, y, CellType.Passive)
		{}

	    public override char GetRepresentation()
	    {
	        return CellRepresentations.FruitCellRepresentation;
	    }

		internal override bool AbleToMove()
		{
			return true;
		}
	}
}
