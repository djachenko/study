package ru.nsu.fit.djachenko.mtk.translator.lexer;

import ru.nsu.fit.djachenko.mtk.translator.buffer.Buffer;

import java.io.IOException;

public class Lexer
{
	private final Buffer buffer;

	private final LexemeFactory factory = LexemeFactory.getInstance();

	Lexer(Buffer buffer)
	{
		this.buffer = buffer;
	}

	Lexeme getLexeme() throws IOException
	{
		trim();

		return parseLexeme();
	}

	private void trim() throws IOException
	{
		for (int c = buffer.peekChar(); !Character.isAlphabetic(c); c = buffer.peekChar())
		{
			switch (c)
			{
				case '/':
					int next = buffer.peekChar(buffer.getPosition() + 1);

					switch (next)
					{
						case '/':
							skipOneLineComment();
							break;

						case '*':
							skipMultilineComment();
							break;

						default:
							buffer.getChar();
							break;
					}

					break;

				default:
					buffer.getChar();
					break;
			}
		}
	}

	private void skipMultilineComment() throws IOException
	{
		while (true)
		{
			int c = buffer.getChar();

			switch (c)
			{
				case '*':
					if (buffer.peekChar(buffer.getPosition() + 1) == '/')
					{
						buffer.getChar();

						return;
					}
					else
					{
						break;
					}
				case '/':
					if (buffer.peekChar(buffer.getPosition() + 1) == '*')
					{
						skipMultilineComment();
					}

					break;

				default:
					break;
			}
		}
	}

	private void skipOneLineComment() throws IOException
	{
		int c = buffer.getChar();

		while (c != '\n')
		{
			c = buffer.getChar();
		}
	}

	private Lexeme parseLexeme() throws IOException
	{
		int c = buffer.peekChar();

		int line = buffer.getLine();
		int column = buffer.getColumn();

		if (Character.isAlphabetic(c))
		{
			StringBuilder builder = new StringBuilder();

			while (Character.isAlphabetic(c) || Character.isDigit(c))
			{
				builder.append(buffer.getChar());
				c = buffer.peekChar();
			}

			return factory.getLexeme(builder.toString(), line, column);
		}
		else if (Character.isDigit(c))
		{
			StringBuilder builder = new StringBuilder();

			while (Character.isDigit(c))
			{
				builder.append(buffer.getChar());
				c = buffer.peekChar();
			}

			return factory.getLexeme(builder.toString(), line, column);
		}
		else
		{
			return factory.getLexeme(String.valueOf(c), line, column);
		}
	}
}
