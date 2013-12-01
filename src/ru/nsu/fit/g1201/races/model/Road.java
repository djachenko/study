package ru.nsu.fit.g1201.races.model;

import ru.nsu.fit.g1201.races.communication.RoadShiftedMessage;
import ru.nsu.fit.g1201.races.model.cells.Cell;
import ru.nsu.fit.g1201.races.model.cells.CellFactory;

import java.util.LinkedList;
import java.util.List;

public class Road
{
	private final Race race;

	private final int width;
	public static final int HEIGHT = 15;

	private LinkedList<RoadLine> road = new LinkedList<>();
	private final RoadLine templateLine;

	private List<Barrier> barriers = new LinkedList<>();

	private int shiftCount = 0;

	private final CellFactory factory = CellFactory.getInstance();

	Road(Race race, int width)
	{
		this.race = race;
		this.width = width;
		templateLine = new RoadLine(width);

		for (int i = 0; i < HEIGHT; i++)
		{
			road.add(templateLine.clone());
		}
	}

	public int getWidth()
	{
		return width;
	}

	public int getHeight()
	{
		return HEIGHT;
	}

	public RoadLine getLine(int i)
	{
		return road.get(i - shiftCount);
	}

	public Cell at(int x, int y)
	{
		return road.get(y - shiftCount).at(x);
	}

	boolean ableToReplace(int x, int y)
	{
		return !(x < 0 || x >= width || y < shiftCount || y >= HEIGHT + shiftCount) && at(x, y).ableToReplace();
	}

	public void replace(int x, int y, Cell cell)
	{
		if (ableToReplace(x, y))
		{
			getLine(y).replace(x, cell);
		}
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return at(x, y).ableToMove(direction);
	}

	public synchronized void move(int x, int y, Direction direction)
	{
		at(x, y).move(direction);
		replace(x, y, factory.getAsphaltCell());
	}

	synchronized void shift()
	{
		road.remove();
		road.add(templateLine.clone());

		shiftCount++;

		LinkedList<Barrier> temp = new LinkedList<>();

		for (Barrier barrier : barriers)
		{
			barrier.draw(this, HEIGHT - 1 + shiftCount);

			if (!barrier.isAlreadyDrawn(HEIGHT - 1 + shiftCount))
			{
				temp.add(barrier);
			}
		}

		barriers = temp;

		race.send(new RoadShiftedMessage(road.get(HEIGHT - 1)));
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
		StringBuilder buffer = new StringBuilder();

		for (int i = HEIGHT - 1; i >= 0; i--)
		{
			if (i + shiftCount < 10)
			{
				buffer.append('0');
			}
			
			buffer.append(i + shiftCount).append(' ').append(road.get(i));
		}

		System.out.println(buffer);
	}
}
