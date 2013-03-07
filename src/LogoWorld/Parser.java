package LogoWorld;

import java.io.File;
import java.io.FileInputStream;
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
		if (input.hasNextLine())
		{
			return input.nextLine().trim().replaceAll("\\s+", " ").split(" ");
		}

		return null;
	}

	public boolean ready()
	{
		return input.hasNextLine();
	}
}
