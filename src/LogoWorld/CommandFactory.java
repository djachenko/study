package logoworld;

import logoworld.commands.Command;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;

public class CommandFactory
{
	private Properties props;
	private HashMap<String, Class<Command>> commands;

	private static Logger logger = Logger.getLogger(CommandFactory.class);

	CommandFactory(String configName)
	{
		props = new Properties();
		commands = new HashMap<>();

		try (InputStream configFile = ClassLoader.getSystemResourceAsStream(configName))
		{
			props.load(configFile);
		}
		catch (IOException excptn)
		{
			System.err.println("Error while opening config file: " + excptn.getLocalizedMessage());

			logger.fatal("Error while configuring factory", new Throwable("Error while configuring factory", excptn));
		}

		logger.info("Factory successfully configured");
	}

	private void set(String name)
	{
		try
		{
			Class currentCommand = Class.forName(props.getProperty(name));

			if (Command.class.isAssignableFrom(currentCommand))//if this command can be cast to logoworld.Command
			{
				commands.put(name, currentCommand);//then add to map

				logger.info("Command class\"" + name + "\" loaded.");
			}
		}
		catch (ClassNotFoundException e)
		{
			logger.error("Unable to load class \"" + name + '\"');
			e.printStackTrace();
		}
	}

	public Command get(String name)
	{
		logger.info("Command " + name + " requested.");

		if (!commands.containsKey(name))
		{
			logger.info("Command " + name + " not loaded");

			set(name);
		}

		try
		{
			return commands.get(name).newInstance();
		}
		catch (InstantiationException | IllegalAccessException e)
		{
			logger.error("Something happened while command instantiantion " + e.getLocalizedMessage());
			e.printStackTrace();
		}

		return null;
	}
}
