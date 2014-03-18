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

	Lexeme getLexeme(String representation, int line, int column)
	{
		if (representation.equals("="))
		{
			return new Lexeme(Lexeme.Type.ASSIGN, line, column);
		}
		else if (representation.equals("double") || representation.equals("int"))
		{
			return new Lexeme(Lexeme.Type.TYPE, line, column);
		}
		else if (representation.equals("print"))
		{
			return new Lexeme(Lexeme.Type.PRINT, line, column);
		}
		else
		{
			return new Lexeme(Lexeme.Type.NAME, line, column);
		}
	}
}
