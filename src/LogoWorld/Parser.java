package logoworld;

import org.apache.log4j.Logger;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Parser
{
	private Scanner input = null;
	private static Logger logger = Logger.getLogger(Parser.class);

	Parser(String inputName)
	{
		try
		{
			input = new Scanner(new File(inputName));

			logger.info("Parser successfully configured");
		}
		catch (FileNotFoundException e)
		{
			logger.error("Error while source opening: " + e.getLocalizedMessage());

			e.printStackTrace();
		}
	}

	public String[] getCommand()
	{
		String current;

		for ( ; ; )
		{
			if (!input.hasNextLine())
			{
				logger.info("Parser reached end of source file.");

				return null;
			}
			else
			{
			    current = input.nextLine().replaceAll("\\s+", " ").trim();

				if (!current.isEmpty())
				{
					return current.split(" ");
				}
			}
		}
	}

	public boolean ready()
	{
		return input.hasNextLine();
	}
}
