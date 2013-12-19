package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.StarterController;
import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.communication.RaceStoppedMessage;
import ru.nsu.fit.g1201.races.communication.RaceStartedMessage;
import ru.nsu.fit.g1201.races.communication.RaceStoppedMessage;
import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.view.activities.HandleMessageTask;
import ru.nsu.fit.g1201.races.view.activities.ViewTaskPerformer;

import javax.swing.*;

public class MainWindow extends JFrame
{
	private RaceView currentRaceView;
	private SelectMapView selectMapView;

	private JPanel currentPanel = null;

	private ViewTaskPerformer performer = new ViewTaskPerformer();

	private StarterController controller;

	public MainWindow(MessageChannel<MessageToView> channelToView, StarterController controller)
	{
		this.controller = controller;

		initUI();

		performer.enqueue(new HandleMessageTask(channelToView, this));
	}

	private void initUI()
	{
		showSelectMapView();

		setLocationRelativeTo(null);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}

	private void changePanelTo(JPanel panel)
	{
		if (currentPanel != null)
		{
			remove(currentPanel);
		}

		add(panel);
		pack();
		setLocationRelativeTo(null);

		currentPanel = panel;
	}

	private void showSelectMapView()
	{
		if (selectMapView == null)
		{
			selectMapView = new SelectMapView(controller);
		}

		changePanelTo(selectMapView);
	}

	private void startRace(Race race)
	{
		currentRaceView = new RaceView(race);

		changePanelTo(currentRaceView);
		currentRaceView.requestFocus();
	}

	public void accept(MessageToView messageToView)
	{
		if (currentRaceView != null)
		{
			messageToView.handle(currentRaceView);
		}
	}

	public void accept(RaceStartedMessage message)
	{
		startRace(message.getRace());
	}

	public void accept(RaceStoppedMessage message)
	{
		showSelectMapView();

		currentRaceView = null;
	}
}
