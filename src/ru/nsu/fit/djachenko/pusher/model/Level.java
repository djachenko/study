package ru.nsu.fit.djachenko.pusher.model;

import ru.nsu.fit.djachenko.pusher.model.cells.Pusher;

import java.io.IOException;

public class Level extends Field
{
	private Pusher pusher;
	private boolean active;

	private final DirectionTransfer directionTransfer;
	private long time;

	private int count;
	public final int id;

	public Level(int id, String levelFile, DirectionTransfer directionTransfer) throws IOException
	{
		super();

		init(levelFile);

		pusher = getPusher();

		this.directionTransfer = directionTransfer;
		this.time = 0;
		this.count = 0;
		this.id = id;
	}

	public void run()
	{
		long start = System.currentTimeMillis();

		synchronized (this)
		{
			active = true;
		}

		while (true)
		{
			synchronized (this)
			{
				if (!active)
				{
					break;
				}
			}

			try
			{
				synchronized (directionTransfer)
				{
					directionTransfer.wait();
				}

				if (!active)
				{
					return;
				}

				movePusher(directionTransfer.getDirection());
				count++;

				synchronized (this)
				{
					notify();//tell view to update
				}
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}

			if (freePoints() == 0)
			{
				active = false;
			}
		}

		long end = System.currentTimeMillis();

		time = end - start;
	}

	public long getTime()
	{
		return time;
	}

	public int getCount()
	{
		return count;
	}

	public void stop()
	{
		synchronized (this)
		{
			active = false;
			notifyAll();
		}
	}

	public void movePusher(Direction dir)
	{
		pusher.move(dir);
	}

	public boolean isActive()
	{
		synchronized (this)
		{
			return active;
		}
	}
}
