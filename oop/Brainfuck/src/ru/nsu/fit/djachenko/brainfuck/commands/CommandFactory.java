package ru.nsu.fit.djachenko.brainfuck.commands;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

public class CommandFactory
{
	private Properties props = new Properties();
	private Map<Character, Class<Command>> commands = new HashMap<>();

	private static Map<String, CommandFactory> factories = new HashMap<>();

	private CommandFactory(String configName)
	{
		try (InputStream configFile = ClassLoader.getSystemResourceAsStream(configName))
		{
			props.load(configFile);
		}
		catch (IOException e)
		{
			System.err.println("Error while opening config file: " + e.getLocalizedMessage());

			throw new RuntimeException(e);
		}
	}

	public static CommandFactory getInstance(String configName)
	{
		if (!factories.containsKey(configName))
		{
			factories.put(configName, new CommandFactory(configName));
		}

		return factories.get(configName);
	}

	private void set(char name)
	{
		try
		{
			Class currentCommand = Class.forName(props.getProperty(String.valueOf(name)));

			if (Command.class.isAssignableFrom(currentCommand))//if this command can be cast to ru.nsu.fit.djachenko.brainfuck.Command
			{
				commands.put(name, currentCommand);//then add to map
			}
		}
		catch (ClassNotFoundException e)
		{
			e.printStackTrace();
		}
	}

	public Command get(char name)
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
			e.printStackTrace();
		}

		return null;
	}
}
