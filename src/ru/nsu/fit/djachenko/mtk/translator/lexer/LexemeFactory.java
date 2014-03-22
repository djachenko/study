package ru.nsu.fit.djachenko.mtk.translator.lexer;

public class LexemeFactory
{
	private static final LexemeFactory instance = new LexemeFactory();

	private LexemeFactory()
	{}

	static LexemeFactory getInstance()
	{
		return instance;
	}

	Lexeme getLexeme(Lexeme.Type type, int line, int column)
	{
		return new Lexeme(type, line, column);
	}

	Lexeme getLexeme(Lexeme.Type type, String value, int line, int column)
	{
		return new Lexeme(type, value, line, column);
	}
}
