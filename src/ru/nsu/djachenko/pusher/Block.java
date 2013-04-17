package ru.nsu.djachenko.pusher;

import ru.nsu.djachenko.pusher.exceptions.PusherException;

public class Block
{
	protected World world = null;//MUST BE PRIVATE
	private int x = -1;
	private int y = -1;

	public Block(World iWorld, int iX, int iY)
	{
		this.world = iWorld;
		this.x = iX;
		this.y = iY;
	}

	public void moveLeft() throws PusherException
	{
		if (world.getCell(x - 1, y) == Field.States.FLOOR)
		{
			x--;
		}
	}

	public void moveRight() throws PusherException
	{
		if (world.getCell(x - 1, y) == Field.States.FLOOR)
		{
			x++;
		}
	}

	public void moveUp() throws PusherException
	{
		if (world.getCell(x, y + 1) == Field.States.FLOOR)
		{
			y++;
		}
	}

	public void moveDown() throws PusherException
	{
		if (world.getCell(x, y - 1) == Field.States.FLOOR)
		{
			y--;
		}
	}

	public int getX()
	{
		return x;
	}

	public int getY()
	{
		return y;
	}

/*
1. хранить передвигающиеся блоки отдельно от поля, поле - только стены и пространство
2. блоки только в поле
3. и там, и там.
что будет лучше?
и что делать с точками?
*/
}
