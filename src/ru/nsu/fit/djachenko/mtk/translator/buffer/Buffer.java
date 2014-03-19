package ru.nsu.fit.djachenko.mtk.translator.buffer;

import java.io.IOException;
import java.io.Reader;

public class Buffer
{
	private final Reader reader;
	private int position = 0;

	private int line = 0;
	private int column = 0;

	private boolean trigger = false;

	private StringBuffer buffer = new StringBuffer();

	Buffer(Reader reader)
	{
		if (reader == null)
		{
			throw new NullPointerException();
		}

		this.reader = reader;
	}

	public int getChar() throws IOException
	{
		while (!(position < buffer.length()))
		{
			retrieveChar();
		}

		int c = buffer.charAt(position++);

		if (trigger)
		{
			line++;
			column = 0;

			trigger = false;
		}
		else
		{
			column++;
		}

		if (c == '\n')
		{
			trigger = true;
		}

		return c;
	}

	public int peekChar() throws IOException
	{
		return peekChar(position);
	}

	public int peekChar(int index) throws IOException
	{
		while (!(index < buffer.length()))
		{
			retrieveChar();
		}

		return buffer.charAt(index);
	}

	private void retrieveChar() throws IOException
	{
		int nextChar = reader.read();

		if (nextChar == -1)
		{
			throw new BufferException("Attempt to read more characters than program contains");
		}
		else
		{
			buffer.append((char)nextChar);
		}
	}

	public int getLine()
	{
		return line;
	}

	public int getColumn()
	{
		return column;
	}

	public int getPosition()
	{
		return position;
	}
}
