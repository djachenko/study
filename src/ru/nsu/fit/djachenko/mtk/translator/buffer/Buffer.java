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
			column = -1;

			trigger = false;
		}

		if (c == '\n')
		{
			trigger = true;
		}

		column++;

		return c;
	}

	public int peekChar()
	{
		return peekChar(position);
	}

	public int peekChar(int index)
	{
		return buffer.charAt(index);
	}

	private void retrieveChar() throws IOException
	{
		buffer.append(reader.read());
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
