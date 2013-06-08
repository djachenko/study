package ru.nsu.djachenko.pusher.model;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class Controller extends KeyAdapter
{
	private final DirectionTransfer directionTransfer;

	public Controller(DirectionTransfer directionTransfer)
	{
		this.directionTransfer = directionTransfer;
	}

	@Override
	public void keyPressed(KeyEvent e)
	{
		int key = e.getKeyCode();

		synchronized (directionTransfer)
		{
			switch (key)
			{
				case KeyEvent.VK_LEFT:
					directionTransfer.setDirection(Direction.LEFT);
					directionTransfer.notifyAll();
					break;
				case KeyEvent.VK_RIGHT:
					directionTransfer.setDirection(Direction.RIGHT);
					directionTransfer.notifyAll();
					break;
				case KeyEvent.VK_DOWN:
					directionTransfer.setDirection(Direction.DOWN);
					directionTransfer.notifyAll();
					break;
				case KeyEvent.VK_UP:
					directionTransfer.setDirection(Direction.UP);
					directionTransfer.notifyAll();
					break;
			}
		}
	}
}
