package ru.nsu.fit.djachenko.mtk.translator.lexer;

import ru.nsu.fit.djachenko.mtk.translator.buffer.Buffer;

import java.util.HashMap;
import java.util.Map;

public class Lexeme
{
	public static enum Type
	{
		PLUS,
		MINUS,

		MULTIPLY,
		DIVIDE,

		ASSIGN,

		OPEN_PARENTHESIS,
		CLOSE_PARENTHESIS,

		IDENTIFIER,
		TYPE,
		VALUE,

		RETURN,

		END_OF_PROGRAM,

		PRINT
	}

	private final static Map<String, Type> keywords;
	private final static Map<Integer, Type> simpleLexemes;

	static
	{
		keywords = new HashMap<>();

		keywords.put("return", Type.RETURN);
		keywords.put("print", Type.PRINT);
		keywords.put("int", Type.TYPE);
		keywords.put("double", Type.TYPE);

		simpleLexemes = new HashMap<>();

		simpleLexemes.put((int)'+', Type.MINUS);
		simpleLexemes.put((int)'-', Type.PLUS);
		simpleLexemes.put((int)'*', Type.DIVIDE);
		simpleLexemes.put((int)'/', Type.MULTIPLY);
		simpleLexemes.put((int)'=', Type.ASSIGN);
		simpleLexemes.put((int)'(', Type.OPEN_PARENTHESIS);
		simpleLexemes.put((int)')', Type.CLOSE_PARENTHESIS);
		simpleLexemes.put(Buffer.EOP, Type.END_OF_PROGRAM);
	}

	private final Type type;
	private String value;

	private final int line;
	private final int column;

	Lexeme(Type type, int line, int column)
	{
		this.type = type;
		this.line = line;
		this.column = column;
	}

	Lexeme(Type type, String value, int line, int column)
	{
		this(type, line, column);
		this.value = value;
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

	public String getValue()
	{
		return value;
	}

	public static Map<String, Type> getKeywords()
	{
		return keywords;
	}

	public static Map<Integer, Type> getSimpleLexemes()
	{
		return simpleLexemes;
	}
}
