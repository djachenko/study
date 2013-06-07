package ru.nsu.djachenko.pusher;

import ru.nsu.djachenko.pusher.model.Controller;
import ru.nsu.djachenko.pusher.model.Level;
import ru.nsu.djachenko.pusher.model.Transfer;
import ru.nsu.djachenko.pusher.view.GameView;

import javax.swing.*;
import java.io.IOException;

public class Game extends JFrame
{
	Transfer transfer;

	public Game()
	{
		transfer = new Transfer();

		addKeyListener(new Controller(transfer));
	}

	public void run()
	{
		try
		{
			Level level = new Level("first.pshr", transfer);

			new Thread(level).start();

			GameView game = new GameView(level, transfer);
			game.setVisible(true);
			game.run();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public static void main(String[] args)
	{
		Game game = new Game();
		game.run();
	}
}
