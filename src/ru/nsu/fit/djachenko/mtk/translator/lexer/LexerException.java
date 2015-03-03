package ru.nsu.fit.djachenko.mtk.translator.lexer;

public class LexerException extends Exception
{
	public LexerException(String message)
	{
		super(message);
	}

	LexerException(String message, int line, int column)
	{
		this(message + " at line " + line + ", column " + column);
	}
}
