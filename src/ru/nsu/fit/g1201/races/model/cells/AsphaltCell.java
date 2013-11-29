package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Direction;

public class AsphaltCell extends Cell
{
	@Override
	public boolean ableToMove(Direction direction)
	{
		return true;
	}

	@Override
	public void move(Direction direction)
	{
	}

	@Override
	public char getRepresentation()
	{
		return ' ';
	}
}
