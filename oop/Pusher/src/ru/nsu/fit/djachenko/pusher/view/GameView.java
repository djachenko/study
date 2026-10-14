package ru.nsu.fit.djachenko.pusher.view;

import ru.nsu.fit.djachenko.pusher.Game;
import ru.nsu.fit.djachenko.pusher.model.Controller;
import ru.nsu.fit.djachenko.pusher.model.DirectionTransfer;
import ru.nsu.fit.djachenko.pusher.model.RecordTable;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameView extends JFrame
{
	private Game origin;

	private Timer timer;
	private final int delay = 100;

	private GreetingScreen greetingScreen;
	private LevelView currentlevelView;

	private JMenuItem reset;

	private boolean active;

	public GameView(Game origin)
	{
		this.origin = origin;

		greetingScreen = new GreetingScreen(origin.getNumberTransfer(), Game.countLevels());

		timer = new Timer(delay, new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				iteration();
			}
		});

		initUI(origin.getDirectionTransfer());

		timer.start();

		active = false;
	}

	public void initUI(DirectionTransfer directionTransfer)
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

			reset = new JMenuItem("Reset the game");
			{
				reset.addActionListener(new ActionListener()
				{
					@Override
					public void actionPerformed(ActionEvent e)
					{
						if(JOptionPane.OK_OPTION == JOptionPane.showConfirmDialog(programMenu,
								"Are you sure to clear record table?",
								"Confirmation",
								JOptionPane.OK_CANCEL_OPTION))
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

		add(greetingScreen);
		pack();

		setTitle("Pusher");
		setLocationRelativeTo(null);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		addKeyListener(new Controller(directionTransfer));

		setVisible(true);
	}

	public void startLevel()
	{
		JMenu game = getJMenuBar().getMenu(0);

		JMenuItem exit = game.getItem(2);

		game.remove(reset);
		game.remove(exit);

		JMenuItem restart = new JMenuItem("Restart");
		{
			restart.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e)
				{
					origin.restart();
					stopLevel(true);
					startLevel();
				}
			});
		}

		game.add(restart);

		JMenuItem mainMenu = new JMenuItem("Main menu");
		{
			mainMenu.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent e)
				{
					origin.stop();

					stopLevel(true);
				}
			});
		}

		game.add(mainMenu);
		game.add(exit);

		remove(greetingScreen);

		currentlevelView = new LevelView(origin.getCurrentLevel());

		add(currentlevelView);
		pack();
		requestFocusInWindow();

		active = true;
		currentlevelView.start();
	}

	public void stopLevel(boolean isHard)
	{
		if (currentlevelView == null)
		{
			return;
		}

		if (!isHard)
		{
			System.out.println("soft");
			currentlevelView.stop();
		}
		else
		{
			System.out.println("hard");
			currentlevelView.hardStop();
		}

		remove(currentlevelView);

		currentlevelView = null;

		active = false;

		JMenu game = getJMenuBar().getMenu(0);

		JMenuItem restart = game.getItem(1);
		JMenuItem mainMenu = game.getItem(2);
		JMenuItem exit = game.getItem(3);

		game.remove(restart);
		game.remove(mainMenu);
		game.remove(exit);

		game.add(reset);
		game.add(exit);

		add(greetingScreen);
		pack();
		requestFocusInWindow();
	}

	public void iteration()
	{
		if (origin.isActive() != this.active)
		{
			if (!origin.isActive())
			{
				stopLevel(false);
			}
			else
			{
				startLevel();
			}
		}
	}
}
