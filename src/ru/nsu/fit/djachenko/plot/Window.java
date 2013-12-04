package ru.nsu.fit.djachenko.plot;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class Window extends JFrame
{
	JPanel currentPanel;

	Window(final List<JPanel> panels)
	{
		initUI(panels.get(0));

		new Timer(500, new ActionListener()
		{
			int i = 1;

			@Override
			public void actionPerformed(ActionEvent e)
			{
				setPanel(panels.get(i));

				i++;
				i %= panels.size();
			}
		}).start();
	}

	private void initUI(JPanel panel)
	{
		add(panel);
		currentPanel = panel;
		pack();
		setLocationRelativeTo(null);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}

	void setPanel(JPanel panel)
	{
		remove(currentPanel);
		add(panel);
		pack();
		repaint();
		currentPanel = panel;
	}
}
