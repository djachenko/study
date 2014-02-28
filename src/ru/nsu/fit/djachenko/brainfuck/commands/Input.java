package ru.nsu.fit.djachenko.brainfuck.commands;

import ru.nsu.fit.djachenko.brainfuck.BadCommandException;
import ru.nsu.fit.djachenko.brainfuck.DataManager;
import ru.nsu.fit.djachenko.brainfuck.Interpreter;

import java.io.IOException;
import java.io.InputStreamReader;

public class Input implements Command
{
	private static final InputStreamReader reader = new InputStreamReader(System.in);

	@Override
	public void run(DataManager dataManager, Interpreter caller) throws BadCommandException
	{
		try
		{
			dataManager.write(reader.read());
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
