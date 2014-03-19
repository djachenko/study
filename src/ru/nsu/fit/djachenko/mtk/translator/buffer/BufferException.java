package ru.nsu.fit.djachenko.mtk.translator.buffer;

import java.io.IOException;

public class BufferException extends IOException
{
	BufferException(String message)
	{
		super(message);
	}
}
