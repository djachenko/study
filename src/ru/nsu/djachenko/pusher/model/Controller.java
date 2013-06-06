package ru.nsu.djachenko.pusher.model;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class Controller extends KeyAdapter
{
	private Transfer transfer;

	public Controller(Transfer transfer)
	{
		this.transfer = transfer;
	}

	@Override
	public void keyPressed(KeyEvent e)
	{
		int key = e.getKeyCode();

		synchronized (transfer)
		{
			switch (key)
			{
				case KeyEvent.VK_LEFT:
					System.out.println("left");
					transfer.setDirection(Direction.LEFT);
					break;
				case KeyEvent.VK_RIGHT:
					System.out.println("right");
					transfer.setDirection(Direction.RIGHT);
					break;
				case KeyEvent.VK_DOWN:
					System.out.println("down");
					transfer.setDirection(Direction.DOWN);
					break;
				case KeyEvent.VK_UP:
					System.out.println("up");
					transfer.setDirection(Direction.UP);
					break;
			}

			transfer.notify();
		}
	}
}
