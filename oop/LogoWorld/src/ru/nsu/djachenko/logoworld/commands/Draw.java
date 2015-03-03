package ru.nsu.djachenko.logoworld.commands;

import ru.nsu.djachenko.logoworld.AP;
import ru.nsu.djachenko.logoworld.BadCommandException;
import org.apache.log4j.Logger;

public class Draw implements Command
{
	private static Logger logger = Logger.getLogger(Draw.class);

	@Override
	public void run(AP ap, String[] args) throws BadCommandException
	{
		logger.info("Command \"Draw\" ran");

		if (args.length > 0)
		{
			throw new BadCommandException("Too many arguments for Draw command");
		}

		ap.setState(true);
	}
}
