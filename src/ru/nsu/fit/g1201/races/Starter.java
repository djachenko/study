package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.view.MainWindow;

public class Starter
{
	public static void main(String[] args)
	{
		MessageChannel<MessageToView> channel = new MessageChannel<>();
		ResultController resultController = new ResultController(channel);
		StarterController controller = new StarterController(channel, resultController);
		new MainWindow(channel, controller).setVisible(true);
	}
}
