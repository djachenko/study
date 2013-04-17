package ru.nsu.djachenko.pusher;

import ru.nsu.djachenko.pusher.exceptions.PusherException;

public class Pusher extends Block//толкатель - это просто управляемый блок. Или нет - вопрос в обработке коллизий
{
	Pusher(World iWorld, int iX, int iY)
	{
		super(iWorld, iX, iY);
	}

	public void moveLeft() throws PusherException
	{
		if (world.getCell(getX() - 1, getY()) == Field.States.BLOCK)
		{
			world.getBlock(getX() - 1, getY()).moveLeft();
		}

		super.moveLeft();
	}

	public void moveRight() throws PusherException
	{
		if (world.getCell(getX() + 1, getY()) == Field.States.BLOCK)
		{
			world.getBlock(getX() + 1, getY()).moveRight();
		}

		super.moveRight();
	}

	public void moveUp() throws PusherException
	{
		if (world.getCell(getX(), getY() + 1) == Field.States.BLOCK)
		{
			world.getBlock(getX(), getY() + 1).moveUp();
		}

		super.moveUp();
	}

	public void moveDown() throws PusherException
	{
		if (world.getCell(getX(), getY() - 1) == Field.States.BLOCK)
		{
			world.getBlock(getX(), getY() - 1).moveDown();
		}

		super.moveDown();
	}
}
