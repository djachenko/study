package logoworld.commands;

import logoworld.AP;
import logoworld.BadCommandException;
import org.apache.log4j.Logger;

public class Move implements Command
{
	enum Direction{L, R, U, D}

	private static Logger logger = Logger.getLogger(Init.class);

	private static final int argsExpectedNumber = 2;

	@Override
	public void run(AP ap, String[] args) throws BadCommandException
	{
		StringBuilder arguments = new StringBuilder();

		for ( String i : args )
		{
			arguments.append(i + ' ');
		}

		logger.info("Command \"Move\" ran with arguments: " + arguments);

		if (args.length < argsExpectedNumber)
		{
			throw new BadCommandException("Not enough arguments");
		}

		if (args.length > argsExpectedNumber)
		{
			throw new BadCommandException("Too many arguments");
		}

		Direction dir;

		try
		{
			dir = Direction.valueOf(args[0]);
		}
		catch (IllegalArgumentException e)
		{
			logger.error("Wrong direction argument \"" + args[0] + "\" in command \"Move\"");

			throw new BadCommandException("Wrong direction argument \"" + args[0] + "\" in command \"Move\"");
		}

		for (int i = 0; i < Integer.parseInt(args[1]); i++)
		{
			switch (dir)
			{
				case L:
					ap.move(ap.getX() - 1, ap.getY());
					break;
				case R:
					ap.move(ap.getX() + 1, ap.getY());
					break;
				case U:
					ap.move(ap.getX(), ap.getY() - 1);
					break;
				case D:
					ap.move(ap.getX(), ap.getY() + 1);
					break;
				default:
					logger.error("WTF?");
			}

			ap.setCell();
		}
	}
}
