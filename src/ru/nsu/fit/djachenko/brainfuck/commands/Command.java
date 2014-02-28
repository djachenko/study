package ru.nsu.fit.djachenko.brainfuck.commands;

import ru.nsu.fit.djachenko.brainfuck.BadCommandException;
import ru.nsu.fit.djachenko.brainfuck.DataManager;
import ru.nsu.fit.djachenko.brainfuck.Interpreter;

public interface Command
{
	void run(DataManager dataManager, Interpreter caller) throws BadCommandException;
}
