package ru.nsu.djachenko.pusher.view;

import ru.nsu.djachenko.pusher.model.Controller;
import ru.nsu.djachenko.pusher.model.Level;
import ru.nsu.djachenko.pusher.model.Transfer;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameView extends JFrame
{
	private Transfer transfer;
	private Level level;

	private LevelView levelView;

	public GameView(Level level, Transfer transfer)
	{
		this.level = level;
		this.transfer = transfer;

		initUI();
	}

	public void initUI()
	{
		setLayout(new BorderLayout());

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

		levelView = new LevelView(level, transfer);

		JPanel panel;

		if (true)
		{
			panel = levelView;
		}
		else
		{
			panel = new HelloScreen();
		}

		add(panel);

		pack();

		setTitle("Pusher");
		setLocationRelativeTo(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		addKeyListener(new Controller(transfer));
	}

	public void run()
	{
		levelView.run();
	}
}
