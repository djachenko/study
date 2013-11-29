package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Direction;

public interface Cell
{
	public abstract boolean ableToMove(Direction direction);
	public abstract void move(Direction direction);
	public abstract char getRepresentation();
}
