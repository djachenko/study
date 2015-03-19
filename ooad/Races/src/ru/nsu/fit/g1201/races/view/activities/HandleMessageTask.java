package ru.nsu.fit.g1201.races.view.activities;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.view.MainWindow;

public class HandleMessageTask implements ViewTask
{
	private final MessageChannel<MessageToView> channel;
	private final MainWindow mainWindow;

	public HandleMessageTask(MessageChannel<MessageToView> channel, MainWindow mainWindow)
	{
		this.channel = channel;
		this.mainWindow = mainWindow;
	}

	@Override
	public void execute()
	{
		MessageToView message = channel.tryGet();

		if (message != null)
		{
			message.handle(mainWindow);
		}
	}

	@Override
	public boolean hasToBeRepeated()
	{
		return true;
	}
}
