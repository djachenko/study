package ru.nsu.djachenko.pusher.exceptions;

public class OutOfFieldException extends PusherException
{
	public OutOfFieldException()
	{
		super();
	}

	public OutOfFieldException(String message)
	{
		super(message);
	}
}
