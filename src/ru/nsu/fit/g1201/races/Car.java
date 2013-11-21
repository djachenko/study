package ru.nsu.fit.g1201.races;

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
		}
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}
}
