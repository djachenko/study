package ru.nsu.fit.g1201.races.cells;

import ru.nsu.fit.g1201.races.Direction;
import ru.nsu.fit.g1201.races.Road;

public class CarCell extends Cell
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

		x += direction.getDx();
		y += direction.getDy();
	}
}
