package ru.nsu.djachenko.pusher.model.cells;

import ru.nsu.djachenko.pusher.model.Direction;
import ru.nsu.djachenko.pusher.model.Field;

public class Wall extends Cell
{
	public Wall(Field field, int x, int y)
	{
		super(Type.WALL, field, x, y);
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
