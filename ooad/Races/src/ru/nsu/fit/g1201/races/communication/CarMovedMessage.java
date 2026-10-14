package ru.nsu.fit.g1201.races.communication;

import ru.nsu.fit.g1201.races.model.Direction;
import ru.nsu.fit.g1201.races.view.RaceView;

public class CarMovedMessage extends MessageToView
{
	private final Direction direction;

	public CarMovedMessage(Direction direction)
	{
		this.direction = direction;
	}

	@Override
	public void handle(RaceView raceView)
	{
		raceView.accept(this);
	}

	public Direction getDirection()
	{
		return direction;
	}
}
