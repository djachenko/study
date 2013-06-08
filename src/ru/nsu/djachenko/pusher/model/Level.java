package ru.nsu.djachenko.pusher.model;

import ru.nsu.djachenko.pusher.model.cells.Pusher;

import java.io.IOException;

public class Level extends Field
{
	private Pusher pusher;
	private boolean active;
	private final DirectionTransfer directionTransfer;

	public Level(String levelFile, DirectionTransfer directionTransfer) throws IOException
	{
		super();

		init(levelFile);

		pusher = getPusher();

		this.directionTransfer = directionTransfer;
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
				synchronized (directionTransfer)
				{
					directionTransfer.wait();
				}

				movePusher(directionTransfer.getDirection());

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
	}

	public void stop()
	{
		active = false;
	}

	public void movePusher(Direction dir)
	{
		pusher.move(dir);
	}

	public boolean isActive()
	{
		return active;
	}
}
