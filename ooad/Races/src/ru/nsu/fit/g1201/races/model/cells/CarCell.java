package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Direction;
import ru.nsu.fit.g1201.races.model.Road;

public class CarCell implements Cell
{
	private int x;
	private int y;
	private Road road;

	CarCell(int x, int y, Road road)
	{
		this.x = x;
		this.y = y;
		this.road = road;
	}

	@Override
	public boolean ableToMove(Direction direction)
	{
		return road.ableToMove(x + direction.getDx(), y + direction.getDy(), direction);
	}

	@Override
	public void move(Direction direction)
	{
		road.move(x + direction.getDx(), y + direction.getDy(), direction);
		road.replace(x + direction.getDx(), y + direction.getDy(), this);

		x += direction.getDx();
		y += direction.getDy();
	}

	@Override
	public char getRepresentation()
	{
		return 'r';
	}

	@Override
	public boolean ableToReplace()
	{
		return true;
	}
}
