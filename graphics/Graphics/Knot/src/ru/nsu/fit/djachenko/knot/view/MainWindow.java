package ru.nsu.fit.djachenko.knot.view;

import ru.nsu.fit.djachenko.knot.model.Knot;

import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MainWindow extends JFrame
{
	public MainWindow(Knot knot)
	{
		initUI(knot);
	}

	private void initUI(Knot knot)
	{
		KnotView knotView = new KnotView(knot);

		getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
		getContentPane().add(new ControlPanel(knotView));
		getContentPane().add(knotView);

		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		addKeyListener(new KeyListener()
		{
			@Override
			public void keyTyped(KeyEvent e)
			{

			}

			@Override
			public void keyPressed(KeyEvent e)
			{
				int key = e.getKeyCode();

				switch (key)
				{
					case KeyEvent.VK_UP:
						knot.turn(Math.toRadians(5), 0, 0);
						break;
					case KeyEvent.VK_DOWN:
						knot.turn(Math.toRadians(-5), 0, 0);
						break;
					case KeyEvent.VK_LEFT:
						knot.turn(0, Math.toRadians(5), 0);
						break;
					case KeyEvent.VK_RIGHT:
						knot.turn(0, Math.toRadians(-5), 0);
						break;
					case KeyEvent.VK_SPACE:
						knot.move(0, 0, 1);
						break;
					case KeyEvent.VK_ENTER:
						knot.move(0, 0, -1);
						break;
				}

				repaint();
			}

			@Override
			public void keyReleased(KeyEvent e)
			{

			}
		});

		pack();
		setLocationRelativeTo(null);

		requestFocus();
		setAutoRequestFocus(true);
	}
}
