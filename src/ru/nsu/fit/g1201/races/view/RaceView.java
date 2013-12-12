package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.communication.CarMovedMessage;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.communication.RoadShiftedMessage;
import ru.nsu.fit.g1201.races.model.Direction;
import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.model.Road;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.LinkedList;
import java.util.List;

public class RaceView extends JPanel
{
	private List<RoadLineView> lines = new LinkedList<>();
	private CarView carView;

	RaceView(Race race)
	{
		initUI(race);
	}

	private void initUI(final Race race)
	{
		setLayout(null);

		Road originRoad = race.getRoad();

		int width = originRoad.getWidth();
		int height = originRoad.getHeight();

		for (int y = height - 1; y >= 0; y--)
		{
			RoadLineView roadLineView = new RoadLineView(originRoad.getLine(height - 1 - y), y);

			lines.add(roadLineView);
			add(roadLineView);
		}

		setPreferredSize(new Dimension(width * CellView.GRIDSIZE, height * CellView.GRIDSIZE));

		carView = new CarView(race.getCar(), height);

		add(carView);
		setComponentZOrder(carView, 0);

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
					case KeyEvent.VK_SPACE:
						race.accelerate();
						break;
					default:
						break;
				}
			}

			@Override
			public void keyReleased(KeyEvent e)
			{
				int key = e.getKeyCode();

				switch (key)
				{
					case KeyEvent.VK_SPACE:
						race.deaccelerate();
						break;
					default:
						break;
				}
			}
		});

		repaint();
	}


	public void accept(MessageToView messageToView)
	{}

	public void accept(RoadShiftedMessage message)
	{
		RoadLineView roadLineView = new RoadLineView(message.getLine(), 0);

		for (RoadLineView line : lines)
		{
			line.move(Direction.DOWN);
		}

		add(roadLineView);
		repaint();

		lines.remove(0);
		lines.add(roadLineView);
	}

	public void accept(CarMovedMessage message)
	{
		carView.move(message.getDirection());
	}
}
