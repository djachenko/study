package ru.nsu.fit.djachenko.brainfuck.commands;

import ru.nsu.fit.djachenko.brainfuck.DataManager;
import ru.nsu.fit.djachenko.brainfuck.Interpreter;

public class StartLoop implements Command
{
	@Override
	public void run(DataManager dataManager, Interpreter caller)
	{
		caller.startSubInterpreter();
	}
}
