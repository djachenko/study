package ru.nsu.fit.g1201.races.view.activities;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;

public class ViewTaskPerformer
{
	private final LinkedList<ViewTask> tasks = new LinkedList<>();
	private static final int DELAY = 10;

	public ViewTaskPerformer()
	{
		new Timer(DELAY, new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				synchronized (tasks)
				{
					int count = tasks.size();

					for (; count > 0; count--)
					{
						ViewTask task = tasks.remove();

						task.execute();

						if (task.hasToBeRepeated())
						{
							tasks.add(task);
						}
					}
				}
			}
		}).start();
	}

	public void enqueue(ViewTask task)
	{
		synchronized (tasks)
		{
			tasks.add(task);
		}
	}
}
