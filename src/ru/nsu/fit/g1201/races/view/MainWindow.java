package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.model.Direction;
import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.view.activities.HandleMessageTask;
import ru.nsu.fit.g1201.races.view.activities.ViewTask;
import ru.nsu.fit.g1201.races.view.activities.ViewTaskPerformer;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MainWindow extends JFrame
{
	private RaceView currentRaceView;

	private ViewTaskPerformer performer = new ViewTaskPerformer();

	public MainWindow(Race race, MessageChannel<MessageToView> channel)
	{
		initUI(race);

		performer.enqueue(new HandleMessageTask(channel, this));
	}

	private void initUI(final Race race)
	{
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
					case KeyEvent.VK_LEFT:
						race.moveCar(Direction.LEFT);
						break;
					case KeyEvent.VK_RIGHT:
						race.moveCar(Direction.RIGHT);
						break;
					default:
						break;
				}
			}

			@Override
			public void keyReleased(KeyEvent e)
			{

			}
		});

		currentRaceView = new RaceView(race);
		add(currentRaceView);
		pack();

		setLocationRelativeTo(null);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}

	public void accept(MessageToView messageToView)
	{
		if (currentRaceView != null)
		{
			messageToView.handle(currentRaceView);
		}
	}
}
