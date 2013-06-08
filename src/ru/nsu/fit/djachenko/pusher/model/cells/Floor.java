package ru.nsu.fit.djachenko.pusher.model.cells;

import ru.nsu.fit.djachenko.pusher.model.Direction;
import ru.nsu.fit.djachenko.pusher.model.Field;

public class Floor extends Cell
{
	public Floor(Field field, int x, int y)
	{
		super(Type.FLOOR, field, x, y);
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
