package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Road;

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

	public Cell getBarrierCell()
	{
		return new BarrierCell();
	}
}
