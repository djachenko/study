package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.model.MapList;
import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.model.RaceParameters;

public class StarterController extends Thread
{
	private MapList mapList = MapList.getInstance();

	private final MessageChannel<MessageToView> channel;

	public StarterController(MessageChannel<MessageToView> channel)
	{
		this.channel = channel;
	}

	public void startNewRace(RaceParameters parameters)
	{
		new Race(parameters, channel).start();
	}
}
