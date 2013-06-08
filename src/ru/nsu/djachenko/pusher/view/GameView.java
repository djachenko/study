package ru.nsu.djachenko.pusher.view;

import ru.nsu.djachenko.pusher.model.Controller;
import ru.nsu.djachenko.pusher.model.DirectionTransfer;
import ru.nsu.djachenko.pusher.model.Level;
import ru.nsu.djachenko.pusher.model.NumberTransfer;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameView extends JFrame implements Runnable
{
	private DirectionTransfer directionTransfer;
	private final NumberTransfer numberTransfer;
	private Level[] levels;

	private LevelView[] levelViews;
	private GreetingScreen greetingScreen;

	public GameView(Level[] levels, DirectionTransfer directionTransfer, NumberTransfer numberTransfer)
	{
		this.levels = levels;
		this.directionTransfer = directionTransfer;
		this.numberTransfer = numberTransfer;

		levelViews = new LevelView[levels.length];

		for (int i = 0; i < levelViews.length; i++)
		{
			levelViews[i] = new LevelView(levels[i]);
		}

		greetingScreen = new GreetingScreen(numberTransfer, levels.length);

		initUI();
	}

	public void initUI()
	{
		JMenuBar programMenu = new JMenuBar();

		JMenu game = new JMenu("Game");
		{
			JMenuItem scores = new JMenuItem("Scores");
			JMenuItem reset = new JMenuItem("Reset the game");
			JMenuItem exit = new JMenuItem("Exit");

			exit.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e)
				{
					System.exit(0);
				}
			});

			game.add(scores);
			game.add(reset);
			game.add(exit);
		}

		JMenu help = new JMenu("Help");
		{
			JMenuItem view = new JMenuItem("View help");
			JMenuItem about = new JMenuItem("About");

			help.add(view);
			help.add(about);
		}

		programMenu.add(game);
		programMenu.add(help);

		setJMenuBar(programMenu);


		setTitle("Pusher");
		setLocationRelativeTo(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		addKeyListener(new Controller(directionTransfer));

		setVisible(true);
	}

	public void run()
	{
		while (true)
		{
			add(greetingScreen);
			pack();

			synchronized (numberTransfer)
			{
				try
				{
					numberTransfer.wait();
				}
				catch (InterruptedException e)
				{
					e.printStackTrace();
				}
			}

			startLevel(numberTransfer.getNumber());
		}
	}

	public void startLevel(int index)
	{
		remove(greetingScreen);

		add(levelViews[index]);
		pack();

		levelViews[index].run();

		remove(levelViews[index]);

		levelViews[index] = new LevelView(levels[index]);
	}
}
