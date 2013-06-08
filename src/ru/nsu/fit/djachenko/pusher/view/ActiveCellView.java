package ru.nsu.fit.djachenko.pusher.view;

import ru.nsu.fit.djachenko.pusher.model.cells.Cell;

public class ActiveCellView extends CellView
{
	private final Cell origin;
	private int x;
	private int y;

	public ActiveCellView(Cell origin, Type type)
	{
		super(type, origin.getX(), origin.getY());
		//setBorder(BorderFactory.createLineBorder(Type.FLOOR.color, 10));

		this.origin = origin;
		this.x = origin.getX();
		this.y = origin.getY();
	}

	public int X()
	{
		return x;
	}

	public int Y()
	{
		return y;
	}

	public void moveCell(int dx, int dy)
	{
		x += dx;
		y += dy;

		if (origin.type == Cell.Type.BLOCK)
		{
			if (origin.isOnPoint())
			{
				setBackground(Type.BLOCKONPOINT.color);
			}
			else
			{
				setBackground(Type.BLOCK.color);
			}
		}
	}
}
