package ru.nsu.djachenko.pusher.model;

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
			new Level("first.pshr", transfer).start();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public static void main(String[] args)
	{
		Game game = new Game();

		game.setLocationRelativeTo(null);
		game.setVisible(true);

		game.run();
	}
}
