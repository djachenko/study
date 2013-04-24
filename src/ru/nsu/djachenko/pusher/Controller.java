package ru.nsu.djachenko.pusher;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Controller extends KeyAdapter
{
	@Override
	public void keyPressed(KeyEvent e)
	{
		int key = e.getKeyCode();

		switch (key)
		{
			case KeyEvent.VK_LEFT:
				System.out.println("left");
				break;
			case KeyEvent.VK_RIGHT:
				System.out.println("right");
				break;
			case KeyEvent.VK_DOWN:
				System.out.println("down");
				break;
			case KeyEvent.VK_UP:
				System.out.println("up");
				break;
		}
	}

	public static void main(String[] args)
	{

	}
}
