package ru.nsu.djachenko.pusher.cells;

import ru.nsu.djachenko.pusher.Direction;
import ru.nsu.djachenko.pusher.Field;

public class Point extends Cell
{
	public Point(Field field, int x, int y)
	{
		super(0, field, x, y);
	}

	@Override
	public boolean ableToMove(Direction dir, int strength)
	{
		return true;
	}

	@Override
	public void move(Direction dir, int strength)
	{
	}
}
