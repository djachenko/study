package ru.nsu.fit.g1201.races.model;

import ru.nsu.fit.g1201.races.model.cells.Cell;
import ru.nsu.fit.g1201.races.model.cells.CellFactory;

import java.util.Arrays;
import java.util.Iterator;

public class RoadLine implements Cloneable
{
	private Cell[] line;

	RoadLine(int width)
	{
		line = new Cell[width + 2];


		CellFactory factory = CellFactory.getInstance();

		for (int i = 1; i < width + 1; i++)
		{
			line[i] = factory.getAsphaltCell();
		}

		line[0] = line[width + 1] = factory.getBorderCell();
	}

	private RoadLine(RoadLine origin)
	{
		line = Arrays.copyOf(origin.line, origin.line.length);
	}

	@Override
	public RoadLine clone()
	{
		return new RoadLine(this);
	}

	@Override
	public String toString()
	{
		StringBuilder temp = new StringBuilder();

		for (Cell cell : line)
		{
			temp.append(cell.getRepresentation());
		}

		temp.append('\n');

		return temp.toString();
	}

	public Cell at(int x)
	{
		return line[x + 1];
	}

	void replace(int x, Cell cell)
	{
		line[x + 1] = cell;
	}

	public int length()
	{
		return line.length - 2;
	}
}
