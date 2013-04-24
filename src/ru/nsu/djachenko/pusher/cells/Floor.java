package ru.nsu.djachenko.pusher.cells;

import ru.nsu.djachenko.pusher.Direction;
import ru.nsu.djachenko.pusher.Field;

public class Floor extends Cell
{
	public Floor(int weight, Field field, int x, int y)
	{
		super(weight, field, x, y);
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
