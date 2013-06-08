package ru.nsu.fit.djachenko.pusher;

import ru.nsu.fit.djachenko.pusher.model.DirectionTransfer;
import ru.nsu.fit.djachenko.pusher.model.Level;
import ru.nsu.fit.djachenko.pusher.model.NumberTransfer;
import ru.nsu.fit.djachenko.pusher.view.GameView;

import java.io.IOException;

public class Pusher
{
	private final DirectionTransfer directionTransfer;//to tell model where to move
	private final NumberTransfer numberTransfer;//to choose level to start

	private String [] levelNames = {"level0.pshr",
			"level1.pshr",
			"level2.pshr",
			"level3.pshr",
			"level4.pshr",
			"level5.pshr",
			"level6.pshr",
			"level7.pshr",
			"level8.pshr",
			"level9.pshr"};
	private String path = "levels/";

	public Pusher()
	{
		directionTransfer = new DirectionTransfer();
		numberTransfer = new NumberTransfer();
	}

	public void run()
	{
		try
		{
			Level[] levels = new Level[levelNames.length];

			for (int i = 0; i < levels.length; i++)
			{
				levels[i] = new Level(i, path + levelNames[i], directionTransfer);
			}

			new Thread(new GameView(levels, directionTransfer, numberTransfer)).start();//launch graphics

			int index = 0;

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

				Level level = levels[index];

				levels[index] = new Level(index, path + levelNames[index], directionTransfer);

				level.run();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public static void main(String[] args)
	{
		new Pusher().run();
	}
}
