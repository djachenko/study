package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.model.Direction;
import ru.nsu.fit.g1201.races.model.RoadLine;

import javax.swing.*;

public class RoadLineView extends JLabel
{
	RoadLineView(RoadLine line, int y)
	{
		initUI(line, y);
	}

	private void initUI(RoadLine line, int y)
	{
		setLayout(null);

		int width = line.length();
		CellViewFactory factory = CellViewFactory.getInstance();

		for (int x = 0; x < width; x++)
		{
			CellView cellView = factory.getCellView(line.at(x), x, 0);
			add(cellView);
		}

		setBounds(0, y * CellView.GRIDSIZE, width * CellView.GRIDSIZE, 1 * CellView.GRIDSIZE);
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
