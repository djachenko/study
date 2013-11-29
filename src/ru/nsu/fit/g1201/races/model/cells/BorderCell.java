package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Direction;

public class BorderCell extends Cell
{
	@Override
	public boolean ableToMove(Direction direction)
	{
		return false;
	}

	@Override
	public void move(Direction direction)
	{
	}

	@Override
	public char getRepresentation()
	{
		return '#';
	}
}
