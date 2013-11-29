package ru.nsu.fit.g1201.races.cells;

import ru.nsu.fit.g1201.races.Direction;

public abstract class Cell
{
	public abstract boolean ableToMove(Direction direction);
	public abstract void move(Direction direction);
	public abstract char getRepresentation();
}
