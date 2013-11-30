package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Direction;

public class AsphaltCell implements Cell
{
	AsphaltCell(){}

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

	@Override
	public boolean ableToReplace()
	{
		return true;
	}
}
