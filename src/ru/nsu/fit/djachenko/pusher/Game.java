package ru.nsu.fit.djachenko.pusher;

import ru.nsu.fit.djachenko.pusher.model.DirectionTransfer;
import ru.nsu.fit.djachenko.pusher.model.Level;
import ru.nsu.fit.djachenko.pusher.model.NumberTransfer;
import ru.nsu.fit.djachenko.pusher.view.GameView;

import java.io.IOException;

public class Game
{
	private final DirectionTransfer directionTransfer;//to tell model where to move
	private final NumberTransfer numberTransfer;//to choose level to start

	private static String [] levelNames = {"level0.pshr",
			"level1.pshr",
			"level2.pshr",
			"level3.pshr",
			"level4.pshr",
			"level5.pshr",
			"level6.pshr",
			"level7.pshr",
			"level8.pshr",
			"level9.pshr"};
	private static String path = "levels/";

	private boolean active = false;

	private Level currentLevel = null;

	public Game()
	{
		directionTransfer = new DirectionTransfer();
		numberTransfer = new NumberTransfer();
	}

	public void run()
	{
		int index = 0;

		try
		{
			while (true)
			{
				synchronized (numberTransfer)
				{
					try
					{
						numberTransfer.wait();

						index = numberTransfer.getNumber();
					}
					catch (InterruptedException e)
					{
						e.printStackTrace();
					}
				}

				currentLevel = new Level(index, path + levelNames[index], directionTransfer);

				active = true;
				System.out.println("start");
				currentLevel.run();
				System.out.println("end");
				active = false;
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public boolean isActive()
	{
		return active;
	}

	public Level getCurrentLevel()
	{
		return currentLevel;
	}

	public static int countLevels()
	{
		return levelNames.length;
	}

	public void stop()
	{
		currentLevel.stop();
	}

	public DirectionTransfer getDirectionTransfer()
	{
		return directionTransfer;
	}

	public NumberTransfer getNumberTransfer()
	{
		return numberTransfer;
	}

	public static void main(String[] args)
	{
		Game game = new Game();

		new GameView(game);

		game.run();
	}
}
