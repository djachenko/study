package ru.nsu.djachenko.pusher.view;

import javax.swing.*;
import java.awt.*;

public class CellView extends JLabel
{
	public static final int SIZE = 25;//edge size in pixels (cells are square)
	public static final int GRIDSIZE = 26;

	public enum Type
	{
		FLOOR(new Color(64, 70, 64), 1),
		WALL(new Color(150, 150, 150), 1),
		PUSHER(Color.white, 0),
		BLOCK(Color.yellow, 0),
		BLOCKONPOINT(Color.green, 0),
		POINT(Color.red, 1);

		public final Color color;
		public final int order;

		private Type(Color color, int order)
		{
			this.color = color;
			this.order = order;
		}
	}

	public final Type type;

	public CellView(Type type, int x, int y)
	{
		this.type = type;

		setBounds(GRIDSIZE * x, GRIDSIZE * y, SIZE, SIZE);
		setBorder(BorderFactory.createLineBorder(Color.lightGray, 1));
		setBackground(type.color);
		setOpaque(true);
	}
}
