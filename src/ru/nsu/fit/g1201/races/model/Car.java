package ru.nsu.fit.g1201.races.model;

import ru.nsu.fit.g1201.races.model.cells.CellFactory;

public class Car
{
	private final Race race;
	private int x;
	private int y;

	Car(Race race, int x, int y)
	{
		this.race = race;
		this.x = x;
		this.y = y;
	}

	void move(Direction direction)
	{
		switch (direction)
		{
			case FORWARD:
				if (race.ableToMove(x - 1, y + 2, direction) &&
					race.ableToMove(x + 1, y + 2, direction) &&
					race.ableToMove(x - 1, y, direction) &&
					race.ableToMove(x,     y, direction) &&
					race.ableToMove(x + 1, y, direction))
				{
					race.move(x - 1, y + 2, direction);
					race.move(x + 1, y + 2, direction);
					race.move(x - 1, y, direction);
					race.move(x,     y, direction);
					race.move(x + 1, y, direction);

					y += direction.getDy();
				}

				break;
			case LEFT:
			case RIGHT:
				int dx = direction.getDx();

				if (race.ableToMove(x, y, direction) &&
					race.ableToMove(x + dx, y + 1, direction) &&
					race.ableToMove(x, y + 2, direction) &&
					race.ableToMove(x + dx, y + 3, direction))
				{
					race.move(x, y, direction);
					race.move(x + dx, y + 1, direction);
					race.move(x, y + 2, direction);
					race.move(x + dx, y + 3, direction);

					x += direction.getDx();
				}
				break;
			default:
		}
	}

	public void draw(Road road)
	{
		CellFactory factory = CellFactory.getInstance();

		if (x >= 1 && x <= road.getWidth() - 2 && y >= 0 && y <= road.getHeight() - 4)
		{
			for (int j = 0; j < 4; j++)
			{
				int mod = (j + 1) % 2;

				for (int i = -mod; i <= mod; i++)
				{
					road.replace(x + i, y + j, factory.getCarCell(x + i, y + j, road));
				}
			}
		}
	}
}
