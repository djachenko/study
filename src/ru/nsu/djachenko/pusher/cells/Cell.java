package ru.nsu.djachenko.pusher.cells;

import ru.nsu.djachenko.pusher.Direction;
import ru.nsu.djachenko.pusher.Field;

public abstract class Cell
{
	private int weight;
	private Field field;
	private int x;
	private int y;

	public Cell(int weight, Field field, int x, int y)
	{
		this.weight = weight;
		this.field = field;
		this.x = x;
		this.y = y;
	}

	public boolean ableToMove(Direction dir, int strength)
	{
		return field.ableToMove(x, y, dir, strength - weight);
	}

	public void move(Direction dir, int strength)
	{
		if (ableToMove(dir, strength))
		{
			field.move(x, y, dir, strength);

			x += dir.getDx();
			y += dir.getDy();
		}
	}
}
