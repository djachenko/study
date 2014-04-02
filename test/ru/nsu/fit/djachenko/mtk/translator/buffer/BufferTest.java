package ru.nsu.fit.djachenko.mtk.translator.buffer;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import java.io.IOException;
import java.io.StringReader;

public class BufferTest
{
	private String template;
	private Buffer buffer;

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Before
	public void prepare()
	{
		template = "sd hf js\n\nh fsd\nkjh fa\nK hj ka\nsHAW";
		buffer = new Buffer(new StringReader(template));
	}

	@Test
	public void testNextException() throws IOException, BufferException
	{
		for (int i = 0; i < template.length(); i++)
		{
			buffer.nextChar();
		}

		buffer.nextChar();//EOP

		thrown.expect(BufferException.class);

		buffer.nextChar();//and here is exception
	}

	@Test
	public void testNextLineShift() throws IOException, BufferException
	{
		int lineCount = 0;

		for (int i = 0; i < template.length(); i++)
		{
			int c = buffer.peekChar();
			buffer.nextChar();

			if (c == '\n')
			{
				lineCount++;
			}

			Assert.assertEquals(lineCount, buffer.getLine());
		}
	}

	@Test
	public void testNextColumnShift() throws IOException, BufferException
	{
		int columnCount = 0;

		for (int i = 0; i < template.length(); i++)
		{
			Assert.assertEquals(columnCount, buffer.getColumn());

			int c = buffer.peekChar();
			buffer.nextChar();

			if (c == '\n')
			{
				columnCount = 0;
			}
			else
			{
				columnCount++;
			}

			Assert.assertEquals(columnCount, buffer.getColumn());
		}
	}

	@Test
	public void testPeek() throws IOException, BufferException
	{
		for (int i = 0; i < template.length(); i++)
		{
			int c = buffer.peekChar();

			Assert.assertEquals(template.charAt(i), c);

			buffer.nextChar();
		}
	}

	@Test
	public void testPeekException() throws IOException, BufferException
	{
		for (int i = 0; i < template.length(); i++)
		{
			buffer.peekChar();
			buffer.nextChar();
		}

		buffer.peekChar();
		buffer.nextChar();

		thrown.expect(BufferException.class);

		buffer.peekChar();
	}

	@Test
	public void testPeekLineShift() throws IOException, BufferException
	{
		for (int i = 0; i < template.length(); i++)
		{
			int lineCount = buffer.getLine();

			buffer.peekChar();

			Assert.assertEquals(lineCount, buffer.getLine());

			buffer.nextChar();
		}
	}

	@Test
	public void testPeekColumnShift() throws IOException, BufferException
	{
		for (int i = 0; i < template.length(); i++)
		{
			int column = buffer.getColumn();

			buffer.peekChar();

			Assert.assertEquals(column, buffer.getColumn());

			buffer.nextChar();
		}
	}

	@Test
	public void testPeekNextChar() throws IOException, BufferException
	{
		for (int i = 0; i < template.length() - 1; i++)
		{
			int c = buffer.peekNextChar();

			Assert.assertEquals(template.charAt(i + 1), c);

			buffer.nextChar();
		}

		Assert.assertEquals(Buffer.EOP, buffer.peekNextChar());
	}

	@Test
	public void testPeekNextCharException() throws IOException, BufferException
	{
		for (int i = 0; i < template.length(); i++)
		{
			buffer.peekNextChar();
			buffer.nextChar();
		}

		thrown.expect(BufferException.class);

		buffer.peekNextChar();
	}

	@Test
	public void testPeekNextCharLineShift() throws IOException, BufferException
	{
		for (int j = 0; j < template.length(); j++)
		{
			for (int i = 1; i < template.length(); i++)
			{
				int lineCount = buffer.getLine();

				buffer.peekNextChar();

				Assert.assertEquals(lineCount, buffer.getLine());
			}

			buffer.nextChar();
		}
	}

	@Test
	public void testPeekNextCharColumnShift() throws IOException, BufferException
	{
		for (int j = 0; j < template.length(); j++)
		{
			for (int i = 0; i < template.length(); i++)
			{
				int column = buffer.getColumn();

				buffer.peekChar();

				Assert.assertEquals(column, buffer.getColumn());
			}

			buffer.nextChar();
		}
	}

	@Test
	public void testProgramEnded() throws IOException, BufferException
	{
		for (int i = 0; i < template.length(); i++)
		{
			Assert.assertFalse(buffer.programEnded());
			buffer.nextChar();
		}

		Assert.assertFalse(buffer.programEnded());
		buffer.nextChar();

		Assert.assertTrue(buffer.programEnded());
	}
}