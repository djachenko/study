package ru.nsu.fit.djachenko.brainfuck;

import ru.nsu.fit.djachenko.brainfuck.commands.CommandFactory;

public class Interpreter implements Runnable
{
	private Parser parser;
	private DataManager dataManager;

	private boolean enough;

	public Interpreter(Parser parser, DataManager dataManager)
	{
		this.parser = parser;
		this.dataManager = dataManager;
	}

	@Override
	public void run()
	{
		CommandFactory factory = CommandFactory.getInstance("input.txt");

		enough = false;

		for ( ; !enough && parser.ready(); )
		{
			factory.get(parser.getCommand()).run(dataManager, this);
		}
	}

	public void startSubInterpreter()
	{
		int startPointer = parser.setjmp();
		int endPointer = parser.findClosing();

		Interpreter subInterpreter = new Interpreter(parser, dataManager);

		while (dataManager.out() != 0)
		{
			parser.longjmp(startPointer);
			subInterpreter.run();
		}

		parser.longjmp(endPointer + 1);
	}

	public void stop()
	{
		enough = true;
	}
}