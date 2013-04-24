package ru.nsu.djachenko.pusher;

import ru.nsu.djachenko.pusher.cells.Block;
import ru.nsu.djachenko.pusher.cells.Pusher;
import ru.nsu.djachenko.pusher.exceptions.PusherException;

import java.io.IOException;

import static ru.nsu.djachenko.pusher.Field.States.BLOCK;

public class World
{
	private Pusher pusher = null;
	private Block[] blocks = null;
	private Field field = null;

	World(String configFile) throws IOException
	{
		field = new Field();
      	field.init(configFile);

		int width = field.getWidth();
		int height = field.getHeight();

		blocks = new Block[field.countBlocks()];
		int count = 0;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				try
				{
					switch (field.getCell(x, y))
					{
						case BLOCK:
							blocks[count] = new Block(this, x, y);
							break;
						case PUSHER:
							pusher = new Pusher(this, x, y);
							break;
						default:
							break;
					}
				}
				catch (PusherException e)
				{
					System.err.println("How?");
				}
			}
		}
	}

	public Field.States getCell(int x, int y) throws PusherException
	{
		return field.getCell(x, y);
	}

	public Block getBlock(int x, int y) throws PusherException
	{
		if (field.getCell(x, y) != BLOCK)
		{
			throw new PusherException("Requested cell is not a block");
		}
		else
		{
			for (Block i : blocks)
			{
				if (i.getX() == x && i.getY() == y)
				{
					return i;
				}
			}

			throw new PusherException("Requested cell is block, but there is no such block");
		}
	}

	public void movePusher(Direction dir)
	{
		try
		{
			pusher.move(dir);
		}
	}

	public boolean ableToMove(int x, int y, Direction direction)
	{

	}
}
