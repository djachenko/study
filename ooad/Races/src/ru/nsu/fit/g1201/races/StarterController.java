package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.model.RaceParameters;

public class StarterController extends Thread
{
	private final MessageChannel<MessageToView> channel;
	private final ResultController controller;

	public StarterController(MessageChannel<MessageToView> channel, ResultController controller)
	{
		this.channel = channel;
		this.controller = controller;
	}

	public void startNewRace(RaceParameters parameters)
	{
		new Race(parameters, channel, controller).start();
	}
}
