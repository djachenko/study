package LogoWorld;

import LogoWorld.Commands.Command;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;

public class CommandFactory
{
	private Properties props;
	private HashMap<String, Class<Command>> commands;

	private static Logger logger = Logger.getLogger(CommandFactory.class.getName());

	CommandFactory(String configName)
	{
		props = new Properties();
		commands = new HashMap<>();

		try (InputStream configFile = ClassLoader.getSystemResourceAsStream(configName))
		{
			props.load(configFile);
			props.list(System.out);
		}
		catch (IOException excptn)
		{
			System.err.println("Error while opening config file: " + excptn.getLocalizedMessage());
		}

		System.out.println("Logger: " + logger.getName());
	}

	private void set(String name)
	{
		try
		{
			Class currentCommand = Class.forName(props.getProperty(name));

			if (Command.class.isAssignableFrom(currentCommand))
			{
				commands.put(name, currentCommand);
			}
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
