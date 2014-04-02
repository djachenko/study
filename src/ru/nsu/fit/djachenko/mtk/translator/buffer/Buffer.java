package ru.nsu.fit.djachenko.mtk.translator.buffer;

import java.io.IOException;
import java.io.Reader;

public class Buffer
{
	private final Reader reader;
	private int position = 0;

	private int line = 0;
	private int column = 0;

	private boolean ended = false;
	private int endPosition = -1;

	public static final int EOP = -1;

	private final StringBuffer buffer = new StringBuffer();

	public Buffer(Reader reader)
	{
		if (reader == null)
		{
			throw new NullPointerException();
		}

		this.reader = reader;
	}

	public void nextChar() throws IOException, BufferException
	{
		while (!(position < buffer.length()))
		{
			retrieveChar();
		}

		int c = buffer.charAt(position++);

		if (c == '\n')
		{
			line++;
			column = 0;
		}
		else
		{
			column++;
		}
	}

	public int peekChar() throws IOException, BufferException
	{
		return peekChar(position);
	}

	public int peekNextChar() throws IOException, BufferException
	{
		return peekChar(position + 1);
	}

	private int peekChar(int index) throws IOException, BufferException
	{
		while (!(index < buffer.length()))
		{
			retrieveChar();
		}

		if (index == endPosition)
		{
			return EOP;
		}

		return buffer.charAt(index);
	}

	private void retrieveChar() throws IOException, BufferException
	{
		int nextChar = reader.read();

		if (nextChar == -1)
		{
			if (ended)
			{
				throw new BufferException("Attempt to read more characters than program contains");
			}
			else
			{
				endPosition = buffer.length();
				buffer.append((char)0);
				ended = true;
			}
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

	public boolean programEnded()
	{
		return ended;
	}
}
