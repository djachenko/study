package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.cells.Cell;
import ru.nsu.fit.g1201.races.cells.CellFactory;

import java.util.Arrays;
import java.util.LinkedList;

public class Road
{
	private final int width;
	public static final int HEIGHT = 15;

	private LinkedList<Cell[]> road = new LinkedList<>();
	private final Cell[] templateLine;

	private int shiftCount = 0;

	private final CellFactory factory = CellFactory.getInstance();

	Road(int width)
	{
		this.width = width;
		templateLine = new Cell[width + 2];

		for (int i = 1; i < width + 1; i++)
		{
			templateLine[i] = factory.getAsphaltCell();
		}

		templateLine[0] = factory.getBorderCell();
		templateLine[width + 1] = factory.getBorderCell();

		for (int i = 0; i < HEIGHT; i++)
		{
			road.add(Arrays.copyOf(templateLine, templateLine.length));
		}
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return at(x, y).ableToMove(direction);
	}

	public void move(int x, int y, Direction direction)
	{
		at(x, y).move(direction);

		int dx = direction.getDx();
		int dy = direction.getDy();

		replace(x + dx, y + dy, at(x, y));
		replace(x, y, factory.getAsphaltCell());
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return road.size();
	}

	void draw(Car car)
	{
		car.draw(this);
	}

	void replace(int x, int y, Cell cell)
	{
		getLine(y)[x - 1] = cell;
	}

	void shift()
	{
		road.removeFirst();
		road.addLast(Arrays.copyOf(templateLine, templateLine.length));
		shiftCount++;
	}
	
	private Cell[] getLine(int i)
	{
		return road.get(i - shiftCount);
	}

	Cell at(int x, int y)
	{
		return road.get(y - shiftCount)[x - 1];
	}

	void print()
	{
		StringBuffer buffer = new StringBuffer();

		for (int i = HEIGHT - 1; i >= 0; i--)
		{
			if (i + shiftCount < 10)
			{
				buffer.append('0');
			}
			
			buffer.append(i + shiftCount).append(' ');
			
			for (Cell cell : road.get(i))
			{
				buffer.append(cell.getRepresentation());
			}
			
			buffer.append('\n');
		}

		System.out.println(buffer);
	}
}
