using System;
using PacMan.Helpers;
using PacMan.Model.Cells;
using PacMan.Model.Entities;

namespace PacMan.Model
{
	public sealed class FieldLayer
	{
		private Cell[,] Layer { get; set; }

	    public int Width
	    {
	        get { return Layer.GetLength(0); }
	    }

	    public int Height
	    {
            get { return Layer.GetLength(1); }
	    }

        internal bool EventsEnabled { private get; set; }
        public event EventHandler<CoordinateEventArgs> CellChanged;

	    public FieldLayer(int width, int height)
		{
			Layer = new Cell[width, height];
	        EventsEnabled = true;
		}

	    public Cell this[int x, int y]
		{
			get { return Layer[x, y]; }
		}

		internal bool AbleToMove(int x, int y)
		{
			return Layer[x, y] == null || Layer[x, y].AbleToMove();
		}

		internal void MoveCell(int x, int y, Direction direction, GameEntity caller)
		{
			if (this[x, y] != null)
			{
				this[x, y].NotifyMovement(direction, caller);
			}
		}

	    internal void ReplaceCell(int x, int y, Cell newValue = null)
	    {
	        var oldValue = Layer[x, y];
	        Layer[x, y] = newValue;

	        if (EventsEnabled)
	        {
	            CellChanged.Raise(this, new CoordinateEventArgs { CellAdded = newValue, CellRemoved = oldValue });
	        }
	    }

	    internal void RelocateCell(Cell cell, int toX, int toY)
	    {
	        var fromX = cell.X;
	        var fromY = cell.Y;

	        Layer[toX, toY] = cell;
	        Layer[fromX, fromY] = null;
	    }
	}
}
