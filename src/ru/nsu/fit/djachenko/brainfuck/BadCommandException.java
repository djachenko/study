package ru.nsu.fit.djachenko.brainfuck;

public class BadCommandException extends Exception
{
	public BadCommandException(String message)
	{
		super(message);
	}
}