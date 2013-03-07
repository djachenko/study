package LogoWorld;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Parser
{
	private Scanner input = null;

	Parser(String inputName)
	{
		try
		{
			input = new Scanner(new File(inputName));
		}
		catch (FileNotFoundException e)
		{
			System.err.println("Error while source opening: " + e.getLocalizedMessage());
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
