package LogoWorld;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;

public class CommandFactory
{
	Properties props;
	HashMap<String, Class<Command>> commands;

	CommandFactory(String configName)
	{
		props = new Properties();

		try (InputStream configFile = ClassLoader.getSystemResourceAsStream(configName))
		{
			props.load(configFile);
			props.list(System.out);
		}
		catch (IOException excptn)
		{
			System.err.println("Error while opening config file: " + excptn.getLocalizedMessage());
		}
	}

	private void set(String name)
	{
		try
		{
			Class currentCommand = Class.forName(props.getProperty(name));

			commands.put(name, currentCommand);
		}
		catch (ClassNotFoundException e)
		{
			System.err.println("An exception flew when class " + name + " getting");
			e.printStackTrace();
		}
	}

	public Command get(String name)
	{
		if (!commands.containsKey(name))
		{
			set(name);
		}

		try
		{
			return commands.get(name).newInstance();
		}
		catch (InstantiationException | IllegalAccessException e)
		{
			System.out.println("Something happened while command instantiantion " + e.getLocalizedMessage());
			e.printStackTrace();
		}

		return null;
	}
}
