package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.model.Direction;

import javax.swing.*;
import java.awt.*;

public class CellView extends JPanel
{
	public static int SIZE = 25;
	public static int GRIDSIZE = SIZE + 1;

	public enum Type
	{
		BORDER(new Color(1, 1, 1)),
		ASPHALT(new Color(107, 107, 107)),
		CAR(new Color(200, 0, 0));

		private final Color color;

		private Type(Color color)
		{
			this.color = color;
		}

		Color getColor()
		{
			return color;
		}
	}

	CellView(Type type, int x, int y)
	{
		initUI(type, x, y);
	}

	private void initUI(Type type, int x, int y)
	{
		setBounds(GRIDSIZE * x, GRIDSIZE * y, SIZE, SIZE);
		setBorder(BorderFactory.createLineBorder(type.getColor().darker(), 1));
		//setBorder(BorderFactory.createLineBorder(Color.BLACK));
		setBackground(type.getColor());
		setOpaque(true);
	}

	void move(Direction direction)
	{
		int dx = direction.getDx();
		int dy = direction.getDy();

		for (int i = 0; i < GRIDSIZE; i++)
		{
			setLocation(getX() + dx, getY() + dy);
		}
	}
}
