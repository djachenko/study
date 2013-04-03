package logoworld;

import logoworld.commands.Command;

import java.io.IOException;
import java.util.Arrays;

import org.apache.log4j.Logger;

public class LogoWord
{
	static Logger logger = Logger.getLogger(LogoWord.class);

	public static void main(String[] args) throws IOException
	{
		CommandFactory factory = new CommandFactory("input.txt");
		Parser parser = new Parser(args[0]);
		AP field = new AP();

		for ( ; parser.ready(); )
		{
			String[] current = parser.getCommand();

			Command currentCommand = factory.get(current[0]);

			for (String i : current)
			{
				System.out.print('\"' + i + "\" ");
			}

			System.out.println();

			currentCommand.run(field, Arrays.copyOfRange(current, 1, current.length));

			Drawer.draw(field);
		}
	}
}