package ru.nsu.djachenko.logoworld;

public class BadCommandException extends Exception
{
	public BadCommandException(String message)
	{
		super(message);
	}
}