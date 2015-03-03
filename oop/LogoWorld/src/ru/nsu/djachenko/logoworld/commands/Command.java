package ru.nsu.djachenko.logoworld.commands;

import ru.nsu.djachenko.logoworld.AP;
import ru.nsu.djachenko.logoworld.BadCommandException;

public interface Command
{
	void run(AP ap, String[] args) throws BadCommandException;
}
