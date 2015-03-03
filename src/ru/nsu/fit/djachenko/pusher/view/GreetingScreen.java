package ru.nsu.fit.djachenko.pusher.view;

import ru.nsu.fit.djachenko.pusher.model.NumberTransfer;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GreetingScreen extends JPanel
{
	private final NumberTransfer numberTransfer;

	private int size;

	GreetingScreen(NumberTransfer numberTransfer, int size)
	{
		this.numberTransfer = numberTransfer;
		this.size = size;

		initUI();
	}

	public void initUI()
	{
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

		add(Box.createRigidArea(new Dimension(0, 5)));

		int height = 5;

		for (int i = 0; i < size; i++)
		{
			final LevelButton levelButton = new LevelButton("Level " + i, i);

			levelButton.setMinimumSize(new Dimension(100, 30));
			levelButton.setMaximumSize(new Dimension(100, 30));

			levelButton.setAlignmentX(CENTER_ALIGNMENT);

			levelButton.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e)
				{
					numberTransfer.setNumber(levelButton.index);

					synchronized (numberTransfer)
					{
						numberTransfer.notifyAll();
					}
				}
			});

			add(Box.createRigidArea(new Dimension(0, 5)));
			add(levelButton);
			add(Box.createRigidArea(new Dimension(0, 5)));

			height += 40;
		}

		add(Box.createRigidArea(new Dimension(0, 5)));

		height += 5;

		int width = 120;

		setPreferredSize(new Dimension(width, height));
	}
}
