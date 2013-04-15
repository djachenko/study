package ru.nsu.djachenko.pusher;

import ru.nsu.djachenko.pusher.exceptions.OutOfFieldException;

import java.io.*;

public class Field
{
	public enum States
	{
		WALL,
		FLOOR,
		PUSHER,
		BLOCK,
		POINT
	}

	private States [][] field = null;

	public Field(int x, int y)
	{
		field = new States[y][x];
	}

	public States getCell(int x, int y) throws OutOfFieldException
	{
		if (x < 0 || x > this.getWidth() || y < 0 || y > this.getHeight())
		{
			throw new OutOfFieldException();
		}

		return field[y][x];
	}

	public void setCell(int x, int y, States state) throws OutOfFieldException
	{
		if (x < 0 || x > this.getWidth() || y < 0 || y > this.getHeight())
		{
			throw new OutOfFieldException();
		}

		field[y][x] = state;
	}

	public int getWidth()
	{
		if (field.length > 0)
		{
			return field[0].length;
		}
		else
		{
			return 0;
		}
	}

	public int getHeight()
	{
		return field.length;
	}
}
