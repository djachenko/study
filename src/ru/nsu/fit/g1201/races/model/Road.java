package ru.nsu.fit.g1201.races.model;

import ru.nsu.fit.g1201.races.communication.RoadShiftedMessage;
import ru.nsu.fit.g1201.races.model.cells.Cell;
import ru.nsu.fit.g1201.races.model.cells.CellFactory;
import ru.nsu.fit.g1201.races.model.roadmaps.RoadMap;

import java.util.LinkedList;

public class Road
{
	private final Race race;
	private final RoadMap map;

	public static final int HEIGHT = 15;

	private LinkedList<RoadLine> road = new LinkedList<>();

	private int shiftCount = 0;

	private final CellFactory factory = CellFactory.getInstance();

	Road(Race race, RoadMap map)
	{
		this.race = race;
		this.map = map;

		for (int i = 0; i < HEIGHT; i++)
		{
			road.add(map.nextLine());
		}
	}

	public int getWidth()
	{
		return map.width();
	}

	public int getHeight()
	{
		return HEIGHT;
	}

	public synchronized RoadLine getLine(int i)
	{
		return getTableLine(i - shiftCount);
	}

	public synchronized RoadLine getTableLine(int i)
	{
		return road.get(i);
	}

	public Cell at(int x, int y)
	{
		return road.get(y - shiftCount).at(x);
	}

	boolean ableToReplace(int x, int y)
	{
		return !(x < 0 || x >= getWidth() || y < shiftCount || y >= HEIGHT + shiftCount) && at(x, y).ableToReplace();
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
		road.add(map.nextLine());

		shiftCount++;

		race.send(new RoadShiftedMessage(road.get(HEIGHT - 1)));
	}

	void draw(Car car)
	{
		car.draw(this);
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
