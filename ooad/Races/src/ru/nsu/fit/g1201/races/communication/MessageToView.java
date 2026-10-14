package ru.nsu.fit.g1201.races.communication;

import ru.nsu.fit.g1201.races.view.MainWindow;
import ru.nsu.fit.g1201.races.view.RaceView;

public abstract class MessageToView implements Message
{
	public void handle(MainWindow mainWindow)
	{
		mainWindow.accept(this);
	}

	public void handle(RaceView raceView)
	{
		raceView.accept(this);
	}
}