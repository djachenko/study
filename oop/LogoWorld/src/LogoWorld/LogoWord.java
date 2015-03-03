package logoworld;

import logoworld.commands.Command;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.Arrays;

public class LogoWord
{
	private static Logger logger = Logger.getLogger(LogoWord.class);

	public static void main(String[] args) throws IOException
	{
		CommandFactory factory = new CommandFactory("input.txt");
		Parser parser = new Parser(args[0]);
		AP field = new AP();

		for ( ; parser.ready(); )
		{
			String[] current = parser.getCommand();

			Command currentCommand = factory.get(current[0]);

			try
			{
				currentCommand.run(field, Arrays.copyOfRange(current, 1, current.length));
			}
			catch (BadCommandException e)
			{
				e.printStackTrace();
			}

			Drawer.draw(field);
		}
	}
}