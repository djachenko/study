package ru.nsu.fit.g1201.races.communication;

import ru.nsu.fit.g1201.races.model.RoadLine;
import ru.nsu.fit.g1201.races.view.RaceView;

public class RoadShiftedMessage extends MessageToView
{
	private final RoadLine line;

	public RoadShiftedMessage(RoadLine line)
	{
		this.line = line;
	}

	@Override
	public void handle(RaceView raceView)
	{
		raceView.accept(this);
	}

	public RoadLine getLine()
	{
		return line;
	}
}
