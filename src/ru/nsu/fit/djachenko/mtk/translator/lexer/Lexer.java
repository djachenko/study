package ru.nsu.fit.djachenko.mtk.translator.lexer;

import ru.nsu.fit.djachenko.mtk.translator.buffer.Buffer;
import ru.nsu.fit.djachenko.mtk.translator.buffer.BufferException;

import java.io.IOException;
import java.util.Map;

class Lexer
{
	private final Buffer buffer;

	private static final LexemeFactory FACTORY = LexemeFactory.getInstance();
	private static final Map<String, Lexeme.Type> KEYWORDS = Lexeme.getKeywords();
	private static final Map<Integer, Lexeme.Type> SIMPLE_LEXEMES = Lexeme.getSimpleLexemes();

	Lexer(Buffer buffer)
	{
		this.buffer = buffer;
	}

	Lexeme getLexeme() throws IOException, LexerException, BufferException
	{
		trim();

		return parseLexeme();
	}

	private void trim() throws IOException, LexerException, BufferException
	{
		for (int current = buffer.peekChar(); !lexemeStarts(); current = buffer.peekChar())
		{
			switch (current)
			{
				case '/':
					int next = buffer.peekNextChar();

					switch (next)
					{
						case '/':
							skipOneLineComment();
							break;

						case '*':
							skipMultilineComment();
							break;

						default:
							buffer.nextChar();
							break;
					}

					break;

				default:
					buffer.nextChar();
					break;
			}
		}
	}

	private void skipMultilineComment() throws IOException, LexerException, BufferException
	{
		buffer.nextChar();
		buffer.nextChar();

		while (true)
		{
			int c = buffer.peekChar();

			switch (c)
			{
				case Buffer.EOP:
					throw new LexerException("Not closed comment", buffer.getLine(), buffer.getColumn());
				case '*':
					if (buffer.peekNextChar() == '/')
					{
						buffer.nextChar();
						buffer.nextChar();

						return;
					}
					else
					{
						buffer.nextChar();
						break;
					}
				default:
					buffer.nextChar();
					break;
			}
		}
	}

	private void skipOneLineComment() throws IOException, BufferException
	{
		int c = buffer.peekChar();

		while (c != '\n' && c != Buffer.EOP)
		{
			buffer.nextChar();
			c = buffer.peekChar();
		}
	}

	private Lexeme parseLexeme() throws IOException, LexerException, BufferException
	{
		int c = buffer.peekChar();

		if (isSimpleLexeme(c))
		{
			return parseSimpleLexeme();
		}
		else if (Character.isLetter(c))
		{
			return parseName();
		}
		else if (isNumber(c))
		{
			return parseNumber();
		}
		else
		{
			throw new LexerException("Unknown token", buffer.getLine(), buffer.getColumn());
		}
	}

	private Lexeme parseNumber() throws IOException, LexerException, BufferException
	{
		int c = buffer.peekChar();

		int line = buffer.getLine();
		int column = buffer.getColumn();

		StringBuilder builder = new StringBuilder();

		while (Character.isDigit(c))
		{
			builder.append((char)c);

			buffer.nextChar();
			c = buffer.peekChar();
		}
		
		if (c == '.')
		{
			builder.append(c);
			
			buffer.nextChar();
			c = buffer.peekChar();

			while (Character.isDigit(c))
			{
				builder.append((char)c);

				buffer.peekChar();
				c = buffer.peekChar();
			}
		}

		String value = builder.toString();

		if (value.equals("."))
		{
			throw new LexerException("Wrong number", line, column);
		}
		else
		{
			return FACTORY.getLexeme(Lexeme.Type.VALUE, value, line, column);
		}
	}

	private Lexeme parseName() throws IOException, BufferException
	{
		int c = buffer.peekChar();

		int line = buffer.getLine();
		int column = buffer.getColumn();

		StringBuilder builder = new StringBuilder();

		while (Character.isLetterOrDigit(c))
		{
			builder.append(c);

			buffer.nextChar();
			c = buffer.peekChar();
		}

		String name = builder.toString();

		if (KEYWORDS.containsKey(name))
		{
			return FACTORY.getLexeme(KEYWORDS.get(name), name, line, column);
		}
		else
		{
			return FACTORY.getLexeme(Lexeme.Type.IDENTIFIER, name, line, column);
		}
	}

	private Lexeme parseSimpleLexeme() throws IOException, BufferException
	{
		int c = buffer.peekChar();

		int line = buffer.getLine();
		int column = buffer.getColumn();

		Lexeme.Type type = SIMPLE_LEXEMES.get(c);
		
		buffer.nextChar();

		return FACTORY.getLexeme(type, line, column);
	}

	private boolean isNumber(int c)
	{
		return Character.isDigit(c) || c == '.';
	}

	private boolean isSimpleLexeme(int c)
	{
		return SIMPLE_LEXEMES.containsKey(c);
	}

	private boolean lexemeStarts() throws IOException, BufferException
	{
		int c = buffer.peekChar();

		if (c == '/')
		{
			int next = buffer.peekNextChar();

			return next != '/' && next != '*';
		}
		else
		{
			return Character.isLetterOrDigit(c) || isSimpleLexeme(c);
		}
	}
}
