package ru.nsu.djachenko.pusher.view;

import javax.swing.*;
import java.awt.*;

public class HelloScreen extends JPanel
{
	private int width;
	private int height;

	HelloScreen()
	{
		initUI();
	}

	public void initUI()
	{
		BoxLayout layout = new BoxLayout(this, BoxLayout.Y_AXIS);

		setLayout(layout);

		add(Box.createRigidArea(new Dimension(0, 5)));

		height += 5;

		for (int i = 0; i < 5; i++)
		{
			JButton level = new JButton("Level " + i);

			level.setMinimumSize(new Dimension(100, 30)) ;
			level.setMaximumSize(new Dimension(100, 30));

			level.setAlignmentX(CENTER_ALIGNMENT);

			add(Box.createRigidArea(new Dimension(0, 5)));
			add(level);
			add(Box.createRigidArea(new Dimension(0, 5)));

			height += 40;
		}

		add(Box.createRigidArea(new Dimension(0, 5)));

		height += 5;

		width = 120;

		setPreferredSize(new Dimension(width, height));
	}
}
