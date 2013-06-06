package ru.nsu.djachenko.pusher.model.cells;

import ru.nsu.djachenko.pusher.model.Direction;
import ru.nsu.djachenko.pusher.model.Field;

public class Point extends Cell
{
	public Point(Field field, int x, int y)
	{
		super(0, field, x, y);
		super.setOnPoint(true);
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

	@Override
	public void setOnPoint(boolean value)
	{
	}

	@Override
	public boolean isOnPoint()
	{
		return true;
	}
}
