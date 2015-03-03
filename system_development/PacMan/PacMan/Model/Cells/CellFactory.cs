using System;
using System.Collections.Generic;

namespace PacMan.Model.Cells
{
    sealed class CellFactory
	{
		private static readonly Dictionary<int, Func<Field, int, int, Cell>> Creators = new Dictionary<int, Func<Field, int, int, Cell>>();

		private static readonly Lazy<CellFactory> Lazy = new Lazy<CellFactory>(() => new CellFactory());

		public static CellFactory Instance
		{
			get { return Lazy.Value; }
		}

		private CellFactory()
		{
			Register(CellRepresentations.FruitCellRepresentation, FruitCell.Creator);
            Register(CellRepresentations.GhostCellRepresentation, GhostCell.Creator);
            Register(CellRepresentations.PillCellRepresentation, PillCell.Creator);
            Register(CellRepresentations.MegaPillCellRepresentation, MegaPillCell.Creator);
            Register(CellRepresentations.PlayerCellRepresentation, PlayerCell.Creator);
            Register(CellRepresentations.SpaceCellRepresentation, SpaceCell.Creator);
            Register(CellRepresentations.WallCellRepresentation, WallCell.Creator);
		}

		private static void Register(int cellRepresentationChar, Func<Field, int, int, Cell> cellCreator)
		{
			Creators.Add(cellRepresentationChar, cellCreator);
		}

		public Cell Parse(int cellRepresentationChar, Field field, int x, int y)
		{
			return Creators[cellRepresentationChar] == null ? null : Creators[cellRepresentationChar](field, x, y);
		}

        public Cell GetSpaceCell(Field field, int x, int y)
		{
			return Creators[CellRepresentations.SpaceCellRepresentation](field, x, y);
		}
	}
}
