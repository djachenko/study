package ru.nsu.fit.g1201.races.communication;

import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.view.RaceView;

public class RacePausedMessage extends MessageToView
{
	private final Race race;

	public RacePausedMessage(Race race)
	{
		this.race = race;
	}

	@Override
	public void handle(RaceView raceView)
	{
		raceView.accept(this);
	}

	public Race getRace()
	{
		return race;
	}
}
