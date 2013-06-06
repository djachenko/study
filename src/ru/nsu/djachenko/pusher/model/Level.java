package ru.nsu.djachenko.pusher.model;

import ru.nsu.djachenko.pusher.model.cells.Pusher;

import java.io.IOException;

public class Level extends Thread
{
	private Field field;
	private Pusher pusher;
	private boolean active;
	Transfer lock;

	public Level(String levelFile, Transfer lock) throws IOException
	{
		field = new Field();
		field.init(levelFile);

		pusher = field.getPusher();

		this.lock = lock;
	}

	public void run()
	{
		long start = System.currentTimeMillis();

		active = true;

		field.print();

		while (active)
		{
			try
			{
				synchronized (lock)
				{
					lock.wait();
				}

				movePusher(lock.getDirection());
				field.print();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}

			if (field.blocksNotOnPoints() == 0)
			{
				active = false;
			}
		}

		long end = System.currentTimeMillis();
	}

	public void movePusher(Direction dir)
	{
		pusher.move(dir);
	}
}
