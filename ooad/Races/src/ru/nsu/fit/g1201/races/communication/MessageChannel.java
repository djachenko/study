package ru.nsu.fit.g1201.races.communication;

import java.util.LinkedList;
import java.util.Queue;

public class MessageChannel<T extends Message>
{
	private final Queue<T> queue = new LinkedList<>();

	public synchronized T get()
	{
		while (queue.isEmpty())
		{
			try
			{
				wait();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}

		return queue.remove();
	}

	public synchronized T tryGet()
	{
		if (!queue.isEmpty())
		{
			return queue.remove();
		}
		else
		{
			return null;
		}
	}

	public synchronized void set(T message)
	{
		queue.add(message);
		notify();
	}
}
