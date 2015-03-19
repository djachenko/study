package ru.nsu.fit.djachenko.brainfuck;

public class Parser
{
	private String program;
	private int pointer = 0;

	public Parser(String program)
	{
		this.program = program;
	}

	public char getCommand()
	{
		return program.charAt(pointer++);
	}

	public boolean ready()
	{
		return pointer < program.length();
	}

	public int setjmp()
	{
		return pointer;
	}

	public void longjmp(int index)
	{
		pointer = index;
	}

	public int findClosing()
	{
		int count = 0;

		for (int i = pointer; i < program.length(); i++)
		{
			switch (program.charAt(i))
			{
				case '[':
					count++;
					break;

				case ']':
					if (count == 0)
					{
						return i;
					}
					else
					{
						count--;
					}

					break;
				default:
					break;
			}
		}

		return -1;
	}
}
