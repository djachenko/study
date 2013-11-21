package ru.nsu.fit.g1201.races.cells;

import ru.nsu.fit.g1201.races.Road;

public class CellFactory
{
	private static CellFactory instance;

	private static AsphaltCell asphaltCell = new AsphaltCell();
	private static BorderCell borderCell = new BorderCell();

	public static CellFactory getInstance()
	{
		if (instance == null)
		{
			synchronized (CellFactory.class)
			{
				if (instance == null)
				{
					instance = new CellFactory();
				}
			}
		}

		return instance;
	}

	public Cell getCarCell(int x, int y, Road road)
	{
		return new CarCell(x, y, road);
	}

	public Cell getAsphaltCell()
	{
		return asphaltCell;
	}

	public Cell getBorderCell()
	{
		return borderCell;
	}
}
