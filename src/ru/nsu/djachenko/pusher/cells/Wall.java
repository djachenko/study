package ru.nsu.djachenko.pusher.cells;

import ru.nsu.djachenko.pusher.Direction;
import ru.nsu.djachenko.pusher.Field;

public class Wall extends Cell
{
	public Wall(Field field, int x, int y)
	{
		super(1, field, x, y);
	}

	@Override
	public boolean ableToMove(Direction dir, int strength)
	{
		return false;
	}

	@Override
	public void move(Direction dir, int strength)
	{
	}
}
