package ru.nsu.fit.djachenko.pusher.view;

import ru.nsu.fit.djachenko.pusher.model.*;

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
		final JMenuBar programMenu = new JMenuBar();

		JMenu game = new JMenu("Game");
		{
			JMenuItem scores = new JMenuItem("Scores");
			{
				scores.addActionListener(new ActionListener()
				{
					@Override
					public void actionPerformed(ActionEvent e)
					{
						new RecordTableView().setVisible(true);
					}
				});
			}

			JMenuItem reset = new JMenuItem("Reset the game");
			{
				reset.addActionListener(new ActionListener()
				{
					@Override
					public void actionPerformed(ActionEvent e)
					{
						if(JOptionPane.OK_OPTION == JOptionPane.showConfirmDialog(programMenu, "Are you sure to clear record table?", "Confirmation", JOptionPane.OK_CANCEL_OPTION))
						{
							for (int i = 0; i < RecordTable.getInstance().size(); i++)
							{
								RecordTable.getInstance().clear(i);
							}
						}
					}
				});
			}

			JMenuItem exit = new JMenuItem("Exit");
			{
				exit.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e)
				{
					System.exit(0);
				}
			});
			}

			game.add(scores);
			game.add(reset);
			game.add(exit);
		}

		JMenu help = new JMenu("Help");
		{
			JMenuItem view = new JMenuItem("View help");
			{
				view.addActionListener(new ActionListener()
				{
					@Override
					public void actionPerformed(ActionEvent e)
					{
						HelpView.getInstance().setVisible(true);
					}
				});
			}

			JMenuItem about = new JMenuItem("About");
			{
				about.addActionListener(new ActionListener()
				{
					@Override
					public void actionPerformed(ActionEvent e)
					{
						AboutView.getInstance().setVisible(true);
					}
				});
			}

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

	public void startLevel(final int index)
	{
		JMenu game = getJMenuBar().getMenu(0);

		JMenuItem reset = game.getItem(1);
		JMenuItem exit = game.getItem(2);

		game.remove(reset);
		game.remove(exit);

		JMenuItem mainMenu = new JMenuItem("Main menu");
		{
			mainMenu.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e)
				{
					levelViews[index].stop();

					synchronized (directionTransfer)
					{
						directionTransfer.notifyAll();
					}
				}
			});
		}

		game.add(mainMenu);
		game.add(exit);

		remove(greetingScreen);

		add(levelViews[index]);
		pack();

		levelViews[index].run();

		game.remove(mainMenu);
		game.remove(exit);

		game.add(reset);
		game.add(exit);

		remove(levelViews[index]);

		levelViews[index] = new LevelView(levels[index]);
	}
}
