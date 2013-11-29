package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.view.MainWindow;

public class Starter
{
	public static void main(String[] args)
	{
		Race race = new Race();
		new MainWindow(race).setVisible(true);
	}
}
