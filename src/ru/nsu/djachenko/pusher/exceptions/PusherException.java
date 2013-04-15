package ru.nsu.djachenko.pusher.exceptions;

public abstract class PusherException extends NullPointerException
{
	public PusherException()
	{
	}

	public PusherException(String message)
	{
		super(message);
	}
}
