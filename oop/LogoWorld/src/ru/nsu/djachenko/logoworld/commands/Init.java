package ru.nsu.djachenko.logoworld.commands;

import ru.nsu.djachenko.logoworld.AP;
import ru.nsu.djachenko.logoworld.BadCommandException;
import org.apache.log4j.Logger;

public class Init implements Command
{
	private static Logger logger = Logger.getLogger(Init.class);

    @Override
	public void run(AP ap, String[] args) throws BadCommandException
	{
		StringBuilder arguments = new StringBuilder();

		for ( String i : args )
		{
			arguments.append(i).append(' ');
		}

		logger.info("Command \"Init\" ran with arguments: " + arguments);

		if (args.length < 4)
		{
			throw new BadCommandException("Not enough arguments " + args.length);
		}

		if (args.length > 4)
		{
			throw new BadCommandException("Too many arguments");
		}

		Integer[] intArgs = new Integer[args.length];

		for (int i = 0; i < intArgs.length; i++)
		{
			try
			{
				intArgs[i] = Integer.parseInt(args[i]);//можно ли параллельный foreach?
			}
			catch (NumberFormatException e)
			{
				System.err.println("Wrong parameter #" + i + "in Init");
				e.printStackTrace();
			}
		}

		ap.init(intArgs[0], intArgs[1], intArgs[2], intArgs[3]);
	}
}
