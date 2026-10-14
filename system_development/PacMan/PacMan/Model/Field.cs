using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using PacMan.Helpers;
using PacMan.Model.Cells;
using PacMan.Model.Entities;
using PacMan.Model.Entities.Ghosts;
using PacMan.Model.Exceptions;

namespace PacMan.Model
{
	public sealed class Field
    {
	    private FieldLayer Landscape { get; set; }
	    private FieldLayer ActiveCells { get; set; }

	    public Dictionary<CellType, FieldLayer> Layers { get; private set; }
        public IEnumerable<CellType> OrderedTypes { get; private set; }
		
        private CellFactory Factory { get; set; }

	    public int Width { get; private set; }
	    public int Height { get; private set; }

        internal Labyrinth Labyrinth { get; private set; }

	    public event EventHandler FieldUpdated;

	    internal Field()
	    {
            Factory = CellFactory.Instance;

            Layers = new Dictionary<CellType, FieldLayer>();
            OrderedTypes = CellType.Values.OrderBy(type => type.Order);
	    }

	    internal void Init(TextReader reader)
	    {
            Layers.Clear();

		    var sizesLine = reader.ReadLine() ?? "0 0";
			var sizes = sizesLine.Split(' ');

			Width = int.Parse(sizes[0]);
			Height = int.Parse(sizes[1]);

            foreach (var cellType in CellType.Values)
			{
			    Layers[cellType] = new FieldLayer(Width, Height) { EventsEnabled = false };
			}

			ActiveCells = Layers[CellType.Active];
			Landscape = Layers[CellType.Landscape];

			var passMask = new bool[Width, Height];

			for (var y = 0; y < Height; y++)
			{
				for (var x = 0; x < Width; x++)
				{
					var c = reader.Read();
					var parsedCell = Factory.Parse(c, this, x, y);

					Layers[parsedCell.Type].ReplaceCell(x, y, parsedCell);

					if (parsedCell.Type != CellType.Landscape)
					{
					    Landscape.ReplaceCell(x, y, Factory.GetSpaceCell(this, x, y));
					}

					passMask[x, y] = c != CellRepresentations.WallCellRepresentation;
				}

				reader.Read();
				reader.Read();
			}

	        foreach (var layer in Layers.Values)
	        {
	            layer.EventsEnabled = true;
	        }

            FieldUpdated.Raise(this);

            Labyrinth = new Labyrinth(passMask);
	    }

		internal Cell this[int x, int y]
	    {
		    get
		    {
                return (from type in OrderedTypes
		                select Layers[type]
		                into layer
		                where layer != null && layer[x, y] != null
		                select layer[x, y]).FirstOrDefault();
		    }
	    }

		internal bool AbleToMove(int x, int y)
	    {
		    return Layers.Values.All(layer => layer.AbleToMove(x, y));
	    }

		internal void NotifyMovement(int x, int y, Direction direction, GameEntity caller)
		{
		    if (direction != Direction.Place)
		    {
		        foreach (var layer in Layers.Values)
		        {
		            layer.MoveCell(x, y, direction, caller);
		        }
		    }
		}

		internal void ResetActiveCell(int fromX, int fromY, int toX, int toY)
		{
			var cell = ActiveCells[fromX, fromY];

		    RelocateCell(cell, toX, toY);

		    cell.Teleport(toX, toY);
		}

	    internal void RemovePassiveCell(int x, int y)
		{
			Remove(Layers[CellType.Passive][x, y]);
		}

	    private void Remove(Cell cell)
		{
			if (cell == null)
			{
				throw new NullReferenceException("Trying to remove null cell");
			}

		    var x = cell.X;
		    var y = cell.Y;

            if (cell.Type == CellType.Landscape)
            {
                Landscape.ReplaceCell(x, y, Factory.GetSpaceCell(this, x, y));
            }
            else
            {
                Layers[cell.Type].ReplaceCell(x, y);
            }
		}

	    internal void RelocateCell(Cell cell, int toX, int toY)
	    {
            if (cell == null)
            {
                throw new NullReferenceException("Trying to relocate null cell");
            }

            var targetLayer = Layers[cell.Type];

            if (targetLayer[toX, toY] != cell)
            {
                if (targetLayer[toX, toY] != null)
                {
                    throw new PlaceOccupiedException();
                }

                targetLayer.RelocateCell(cell, toX, toY);
            }
	    }
    }
}
