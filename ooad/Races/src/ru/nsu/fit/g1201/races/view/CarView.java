package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.model.Car;
import ru.nsu.fit.g1201.races.model.Direction;

import javax.swing.*;

public class CarView extends JLabel
{
	CarView(Car origin, int roadHeight)
	{
		initUI(origin.getX(), roadHeight);
	}

	private void initUI(int originX, int roadHeight)
	{
		setLayout(null);
		CellViewFactory factory = CellViewFactory.getInstance();

		for (int y = 0; y < 4; y++)
		{
			int mod = y % 2;

			for (int x = 1 - mod; x <= 1 + mod; x++)
			{
				add(factory.getCellView(CellView.Type.CAR, x, y));
			}
		}

		setBounds((originX - 1) * CellView.GRIDSIZE,
				(roadHeight - 4) * CellView.GRIDSIZE,
				3 * CellView.GRIDSIZE,
				4 * CellView.GRIDSIZE);
	}

	void move(Direction direction)
	{
		int dx = direction.getDx();
		int dy = direction.getDy();

		for (int i = 0; i < CellView.GRIDSIZE; i++)
		{
			setLocation(getX() + dx, getY() + dy);
		}
	}
}
