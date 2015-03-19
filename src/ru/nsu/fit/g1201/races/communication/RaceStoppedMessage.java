package ru.nsu.fit.g1201.races.communication;

import ru.nsu.fit.g1201.races.view.MainWindow;

public class RaceStoppedMessage extends MessageToView
{
	@Override
	public void handle(MainWindow mainWindow)
	{
		mainWindow.accept(this);
	}
}
