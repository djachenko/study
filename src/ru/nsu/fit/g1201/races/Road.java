package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.cells.Cell;
import ru.nsu.fit.g1201.races.cells.CellFactory;

import java.util.LinkedList;
import java.util.List;

public class Road
{
	private int width;

	private List<Cell[]> road;

	private final CellFactory factory = CellFactory.getInstance();

	Road(int width)
	{
		this.width = width;

		this.road = new LinkedList<>();
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{
		return road.get(y)[x].ableToMove(direction);
	}

	public void move(int x, int y, Direction direction)
	{
		road.get(y)[x].move(direction);

		int dx = direction.getDx();
		int dy = direction.getDy();

		road.get(y + dy)[x + dx] = road.get(y)[x];
		road.get(y)[x] = factory.getAsphaltCell();
	}

	void add(Car car)
	{
		int x = car.getX();
		int y = car.getY();

		if (x >= 1 && x <= getWidth() - 2 && y >= 0 && y <= getHeight() - 4)
		{
			Cell[] line = road.get(y);

			line[x] = factory.getCarCell(x, y, this);

			line = road.get(y + 1);

			line[x - 1] = factory.getCarCell(x - 1, y + 1, this);
			line[x] = factory.getCarCell(x, y + 1, this);
			line[x + 1] = factory.getCarCell(x + 1, y + 1, this);

			line = road.get(y + 2);

			line[x] = factory.getCarCell(x, y + 2, this);

			line = road.get(y + 3);

			line[x - 1] = factory.getCarCell(x - 1, y + 3, this);
			line[x] = factory.getCarCell(x, y + 3, this);
			line[x + 1] = factory.getCarCell(x + 1, y + 3, this);
		}
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return road.size();
	}
}
