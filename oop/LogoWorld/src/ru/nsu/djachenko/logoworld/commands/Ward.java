package ru.nsu.djachenko.logoworld.commands;

import ru.nsu.djachenko.logoworld.AP;
import ru.nsu.djachenko.logoworld.BadCommandException;
import org.apache.log4j.Logger;

public class Ward implements Command
{
	private static Logger logger = Logger.getLogger(Init.class);

	private static final int argsExpectedNumber = 0;

	@Override
	public void run(AP ap, String[] args) throws BadCommandException
	{
		logger.info("Command \"Ward\" ran");

		if (args.length < argsExpectedNumber)
		{
			throw new BadCommandException("Not enough arguments");
		}

		if (args.length > argsExpectedNumber)
		{
			throw new BadCommandException("Too many arguments");
		}

		ap.setState(false);
	}
}
