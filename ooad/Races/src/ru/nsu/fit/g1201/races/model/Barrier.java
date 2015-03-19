package ru.nsu.fit.g1201.races.model;

import ru.nsu.fit.g1201.races.model.cells.Cell;
import ru.nsu.fit.g1201.races.model.cells.CellFactory;

public class Barrier
{
	private final int x;
	private final int y;

	private final int width;
	private final int height;

	private final Cell[][] representation;

	public Barrier(int x, int y, int width, int height, Race race)
	{
		this.x = x;
		this.y = y;

		this.width = width;
		this.height = height;

		representation = new Cell[height][width];

		CellFactory factory = CellFactory.getInstance();

		for (Cell[] line : representation)
		{
			for (int i = 0; i < line.length; i++)
			{
				line[i] = factory.getBarrierCell(race);
			}
		}
	}

	public void draw(RoadLine roadLine, int lineIndex)
	{
		if (lineIndex >= y && lineIndex < y + height)
		{
			for (int i = 0; i < width; i++)
			{
				roadLine.replace(x + i, representation[lineIndex - y][i]);
			}
		}
	}

	public boolean isAlreadyDrawn(int lastDrawnLine)
	{
		return y + height <= lastDrawnLine;
	}
}
