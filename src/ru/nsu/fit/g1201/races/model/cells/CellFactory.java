package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.model.Road;

import java.util.HashMap;
import java.util.Map;

public class CellFactory
{
	private static CellFactory instance;

	private static AsphaltCell asphaltCell = new AsphaltCell();
	private static BorderCell borderCell = new BorderCell();

	private static Map<Race, Cell> barrierCells = new HashMap<>();

	private CellFactory()
	{}

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

	public synchronized Cell getBarrierCell(Race race)
	{
		if (!barrierCells.containsKey(race))
		{
			barrierCells.put(race, new BarrierCell(race));
		}

		return barrierCells.get(race);
	}
}
