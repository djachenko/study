package ru.nsu.djachenko.pusher.model.cells;

import ru.nsu.djachenko.pusher.model.Direction;
import ru.nsu.djachenko.pusher.model.Field;

public abstract class Cell
{
	private int weight;
	private Field field;
	private int x;
	private int y;

	private boolean onPoint = false;

	public Cell(int weight, Field field, int x, int y)
	{
		this.weight = weight;
		this.field = field;
		this.x = x;
		this.y = y;
	}

	public boolean ableToMove(Direction dir, int strength)
	{
		return strength >= weight && field.ableToMove(x, y, dir, strength - weight);
	}

	public void move(Direction dir, int strength)
	{
		if (ableToMove(dir, strength))
		{
			field.move(x, y, dir, strength);

			x += dir.getDx();
			y += dir.getDy();

			synchronized (this)
			{
				notifyAll();
			}
		}
	}

	public void setOnPoint(boolean value)
	{
		onPoint = value;
	}

	public boolean isOnPoint()
	{
		return onPoint;
	}

	public boolean isBlock()
	{
		return false;
	}
}
