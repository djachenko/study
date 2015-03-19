package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Direction;
import ru.nsu.fit.g1201.races.model.Race;

public class BarrierCell implements Cell
{
	private final Race race;

	BarrierCell(Race race)
	{
		this.race = race;
	}

	@Override
	public boolean ableToMove(Direction direction)
	{
		return true;
	}

	@Override
	public void move(Direction direction)
	{
		race.crash();
	}

	@Override
	public char getRepresentation()
	{
		return '#';
	}

	@Override
	public boolean ableToReplace()
	{
		return false;
	}
}
