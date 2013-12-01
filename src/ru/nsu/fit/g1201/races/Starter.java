package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.view.MainWindow;

public class Starter
{
	public static void main(String[] args)
	{
		MessageChannel<MessageToView> channel = new MessageChannel<>();
		Race race = new Race(channel);
		new MainWindow(race, channel).setVisible(true);
		race.start();
	}
}
