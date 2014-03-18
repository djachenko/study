package ru.nsu.fit.djachenko.mtk.translator.lexer;

public class Lexeme
{
	public static enum Type
	{
		TYPE,
		ASSIGN,
		PRINT,
		NAME
	}

	private final Type type;
	private final int line;
	private final int column;

	Lexeme(Type type, int line, int column)
	{
		this.type = type;
		this.line = line;
		this.column = column;
	}

	public Type getType()
	{
		return type;
	}

	public int getLine()
	{
		return line;
	}

	public int getColumn()
	{
		return column;
	}
}
