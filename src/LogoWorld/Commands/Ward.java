package logoworld.commands;

import logoworld.AP;
import logoworld.BadCommandException;
import org.apache.log4j.Logger;

public class Ward implements Command
{
	private static Logger logger = Logger.getLogger(Init.class);

	private static final int argsExpectedNumber = 0;

	@Override
	public void run(AP ap, String[] args) throws BadCommandException
	{
		StringBuilder arguments = new StringBuilder();

		for ( String i : args )
		{
			arguments.append(i + ' ');
		}

		logger.info("Command \"Teleport\" ran with arguments: " + arguments);

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
