package ru.nsu.djachenko.pusher.model;

import ru.nsu.djachenko.pusher.model.cells.Pusher;

import java.io.IOException;

public class Level extends Field implements Runnable
{
	private Pusher pusher;
	private boolean active;
	Transfer lock;

	public Level(String levelFile, Transfer lock) throws IOException
	{
		super();
		init(levelFile);

		pusher = getPusher();

		this.lock = lock;
	}

	public void run()
	{
		long start = System.currentTimeMillis();

		active = true;

		print();

		while (active)
		{
			try
			{
				synchronized (lock)
				{
					lock.wait();
				}

				movePusher(lock.getDirection());

				synchronized (this)
				{
					notify();
				}

				print();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}

			if (blocksNotOnPoints() == 0)
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
