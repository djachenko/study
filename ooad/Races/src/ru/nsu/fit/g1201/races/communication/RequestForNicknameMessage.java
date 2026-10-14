package ru.nsu.fit.g1201.races.communication;

import ru.nsu.fit.g1201.races.ResultController;
import ru.nsu.fit.g1201.races.view.MainWindow;

public class RequestForNicknameMessage extends MessageToView
{
	private final ResultController controller;

	public RequestForNicknameMessage(ResultController controller)
	{
		this.controller = controller;
	}

	@Override
	public void handle(MainWindow mainWindow)
	{
		mainWindow.accept(this);
	}

	public ResultController getController()
	{
		return controller;
	}
}
