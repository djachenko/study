package ru.nsu.fit.g1201.races.model.cells;

import ru.nsu.fit.g1201.races.model.Direction;

public interface Cell
{
	public boolean ableToMove(Direction direction);
	public void move(Direction direction);
	public char getRepresentation();
	public boolean ableToReplace();
}
