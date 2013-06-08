package ru.nsu.fit.djachenko.pusher.model.cells;

import ru.nsu.fit.djachenko.pusher.model.Direction;
import ru.nsu.fit.djachenko.pusher.model.Field;

public abstract class Cell
{
	private int weight;
	private Field field;
	private int x;
	private int y;

	private boolean onPoint = false;

	public enum Type
	{
		BLOCK('*', 1),
		PUSHER('t', 0),
		POINT('&', -1),
		WALL('x', -1),
		FLOOR('.', -1);

		public final char representation;
		public final int weight;

		private Type(char x, int weight)
		{
			representation = x;
			this.weight = weight;
		}
	}

	public final Type type;

	public Cell(Type type, Field field, int x, int y)
	{
		this.type = type;
		weight = type.weight;
		this.field = field;
		this.x = x;
		this.y = y;
	}

	public boolean ableToMove(Direction dir, int strength)
	{
		return weight != -1 && strength >= weight && field.ableToMove(x, y, dir, strength - weight);//movable and enough mana
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

	public int getX()
	{
		return x;
	}

	public int getY()
	{
		return y;
	}
}
