package ru.nsu.fit.djachenko.mtk.translator.buffer;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.io.StringReader;

public class BufferTest
{
	String template;
	Buffer buffer;

	@Before
	public void prepare()
	{
		template = "sd hf js\nh fsd\nkjh fa\nK hj ka\nsHAW";
		buffer = new Buffer(new StringReader(template));
	}

	@Test
	public void testGet()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				int c = buffer.getChar();

				Assert.assertEquals(template.charAt(i), c);
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testGetException()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				buffer.getChar();
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}

		try
		{
			buffer.getChar();
			Assert.fail();
		}
		catch (IOException e)
		{}
	}

	@Test
	public void testGetLineShift()
	{
		int lineCount = 0;

		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				int c = buffer.getChar();

				Assert.assertEquals(lineCount, buffer.getLine());

				if (c == '\n')
				{
					lineCount++;
				}
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testGetColumnShift()
	{
		int columnCount = 0;
		int prev = -1;

		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				Assert.assertEquals(columnCount, buffer.getColumn());

				int c = buffer.getChar();

				if (prev == '\n')
				{
					columnCount = 0;
				}
				else
				{
					columnCount++;
				}

				Assert.assertEquals(columnCount, buffer.getColumn());

				prev = c;
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testGetPositionShift()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				Assert.assertEquals(i, buffer.getPosition());

				buffer.getChar();

				Assert.assertEquals(i + 1, buffer.getPosition());
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testPeek()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				int c = buffer.peekChar();

				Assert.assertEquals(template.charAt(i), c);

				buffer.getChar();
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testPeekException()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				buffer.peekChar();
			}
			catch (IOException e)
			{
				Assert.fail();
			}

			try
			{
				buffer.getChar();
			}
			catch (IOException e)
			{}
		}

		try
		{
			buffer.peekChar();
			Assert.fail();
		}
		catch (IOException e)
		{}
	}

	@Test
	public void testPeekLineShift()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				int lineCount = buffer.getLine();

				buffer.peekChar();

				Assert.assertEquals(lineCount, buffer.getLine());

				buffer.getChar();
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testPeekColumnShift()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				int column = buffer.getColumn();

				buffer.peekChar();

				Assert.assertEquals(column, buffer.getColumn());

				buffer.getChar();

			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testPeekPositionShift()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				Assert.assertEquals(i, buffer.getPosition());

				buffer.peekChar();

				Assert.assertEquals(i, buffer.getPosition());

				buffer.getChar();
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testParametrizedPeek()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				int c = buffer.peekChar(i);

				Assert.assertEquals(template.charAt(i), c);
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}
	}

	@Test
	public void testParametrizedPeekException()
	{
		for (int i = 0; i < template.length(); i++)
		{
			try
			{
				buffer.peekChar(i);
			}
			catch (IOException e)
			{
				Assert.fail();
			}
		}

		try
		{
			buffer.peekChar(template.length() + 1);
			Assert.fail();
		}
		catch (IOException e)
		{}
	}

	@Test
	public void testParametrizedPeekLineShift()
	{
		for (int j = 0; j < template.length(); j++)
		{
			for (int i = 0; i < template.length(); i++)
			{
				try
				{
					int lineCount = buffer.getLine();

					buffer.peekChar(i);

					Assert.assertEquals(lineCount, buffer.getLine());
				}
				catch (IOException e)
				{
					Assert.fail();
				}
			}

			try
			{
				buffer.getChar();
			}
			catch (IOException e)
			{}
		}
	}

	@Test
	public void testParametrizedPeekColumnShift()
	{
		for (int j = 0; j < template.length(); j++)
		{
			for (int i = 0; i < template.length(); i++)
			{
				try
				{
					int column = buffer.getColumn();

					buffer.peekChar();

					Assert.assertEquals(column, buffer.getColumn());
				}
				catch (IOException e)
				{
					Assert.fail();
				}
			}

			try
			{
				buffer.getChar();
			}
			catch (IOException e)
			{}
		}
	}

	@Test
	public void testParametrizedPeekPositionShift()
	{
		for (int j = 0; j < template.length(); j++)
		{
			for (int i = 0; i < template.length(); i++)
			{
				try
				{
					Assert.assertEquals(j, buffer.getPosition());

					buffer.peekChar();

					Assert.assertEquals(j, buffer.getPosition());
				}
				catch (IOException e)
				{
					Assert.fail();
				}
			}

			try
			{
				buffer.getChar();
			}
			catch (IOException e)
			{}
		}
	}
}