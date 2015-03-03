using System;
using PacMan.Model.Entities;

namespace PacMan.Model.Cells
{
    sealed class GhostCell : Cell
	{
		internal static readonly Func<Field, int, int, Cell> Creator = (field, x, y) => new GhostCell(field, x, y);

		private GhostCell(Field field, int x, int y) : base(field, x, y, CellType.Active)
		{}

	    internal override void NotifyMovement(Direction direction, GameEntity caller)
	    {
	        if (caller != Owner)
	        {
	            base.NotifyMovement(direction, caller);
	        }
	        else
	        {
	            Field.NotifyMovement(X + direction.Dx, Y + direction.Dy, direction, caller);

	            if (Field.AbleToMove(X + direction.Dx, Y + direction.Dy))
	            {
	                Field.RelocateCell(this, X + direction.Dx, Y + direction.Dy);
	                
	                X += direction.Dx;
	                Y += direction.Dy;

	                OnMovement(direction);
	            }
	        }
	    }

	    public override char GetRepresentation()
	    {
	        return CellRepresentations.GhostCellRepresentation;
	    }

		internal override bool AbleToMove()
		{
		    return false;
		}
	}
}
