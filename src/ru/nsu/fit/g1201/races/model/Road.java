package ru.nsu.fit.g1201.races.model;

import ru.nsu.fit.g1201.races.model.cells.Cell;
import ru.nsu.fit.g1201.races.model.cells.CellFactory;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class Road
{
	private final int width;
	public static final int HEIGHT = 15;

	private LinkedList<Cell[]> road = new LinkedList<>();
	private final Cell[] templateLine;

	private List<Barrier> barriers = new LinkedList<>();

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

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return HEIGHT;
	}

	private Cell[] getLine(int i)
	{
		return road.get(i - shiftCount);
	}

	Cell at(int x, int y)
	{
		return road.get(y - shiftCount)[x + 1];
	}

	boolean ableToReplace(int x, int y)
	{
		return !(x < 0 || x >= width || y < shiftCount || y >= HEIGHT + shiftCount);

	}

	void replace(int x, int y, Cell cell)
	{
		if (ableToReplace(x, y))
		{
			getLine(y)[x + 1] = cell;
		}
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return at(x, y).ableToMove(direction);
	}

	public synchronized void move(int x, int y, Direction direction)
	{
		at(x, y).move(direction);

		int dx = direction.getDx();
		int dy = direction.getDy();

		replace(x + dx, y + dy, at(x, y));
		replace(x, y, factory.getAsphaltCell());
	}

	void shift()
	{
		road.remove();
		road.add(Arrays.copyOf(templateLine, templateLine.length));

		shiftCount++;

		for (Barrier barrier : barriers)
		{
			barrier.draw(this, HEIGHT - 1 + shiftCount);
		}
	}

	void draw(Car car)
	{
		car.draw(this);
	}

	void add(Barrier barrier)
	{
		barriers.add(barrier);
	}

	synchronized void print()
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
