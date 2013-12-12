package ru.nsu.fit.g1201.races.communication;

import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.view.MainWindow;

public class RaceStartedMessage extends MessageToView
{
	private final Race race;

	public RaceStartedMessage(Race race)
	{
		this.race = race;
	}

	public Race getRace()
	{
		return race;
	}

	@Override
	public void handle(MainWindow mainWindow)
	{
		mainWindow.accept(this);
	}
}
