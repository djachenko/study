package ru.nsu.fit.djachenko.mtk.translator.parser.expression;

import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexeme;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.*;

import java.io.IOException;
import java.util.Map;

public class ExpressionParser
{
	private final Lexer lexer;
	private final Map<String, Variable> variableMap;

	public ExpressionParser(Lexer lexer)
	{
		this(lexer, null);
	}

	public ExpressionParser(Lexer lexer, Map<String, Variable> variableMap)
	{
		this.lexer = lexer;
		this.variableMap = variableMap;
	}

	public Expression parseExpression() throws IOException, LexerException, ExpressionParserException
	{
		Expression root = parseTerm();

		while (!lexer.programEnded())
		{
			Lexeme currentLexeme = lexer.getLexeme();

			switch (currentLexeme.getType())
			{
				case PLUS:
					root = new Sum(root, parseTerm());
					break;
				case MINUS:
					root = new Sub(root, parseTerm());
					break;
				default:
					lexer.reject();
					return root;
			}
		}

		return root;
	}

	private Expression parseTerm() throws IOException, LexerException, ExpressionParserException
	{
		Expression root = parseFactor();

		while (!lexer.programEnded())
		{
			Lexeme currentLexeme = lexer.getLexeme();

			switch (currentLexeme.getType())
			{
				case MULTIPLY:
					root = new Mul(root, parseFactor());
					break;
				case DIVIDE:
					root = new Div(root, parseFactor());
					break;
				default:
					lexer.reject();
					return root;
			}
		}

		return root;
	}

	private Expression parseFactor() throws IOException, LexerException, ExpressionParserException
	{
		Expression root = parsePower();

		while (!lexer.programEnded())
		{
			Lexeme currentLexeme = lexer.getLexeme();

			switch (currentLexeme.getType())
			{
				case POWER:
					root = new Power(root, parseFactor());
					break;
				default:
					lexer.reject();
					return root;
			}
		}

		return root;
	}

	private Expression parsePower() throws IOException, LexerException, ExpressionParserException
	{
		Lexeme currentLexeme = lexer.getLexeme();

		switch (currentLexeme.getType())
		{
			case MINUS:
				return new UnaryMinus(parsePower());
			default:
				lexer.reject();
				return parseAtom();
		}
	}

	private Expression parseAtom() throws IOException, LexerException, ExpressionParserException
	{
		Lexeme lexeme = lexer.getLexeme();

		switch (lexeme.getType())
		{
			case VALUE:
				return new Constant(lexeme.getValue());
			case IDENTIFIER:
				return variableMap.get(lexeme.getValue());
			case OPEN_PARENTHESIS:
				Expression expression = parseExpression();

				lexeme = lexer.getLexeme();

				if (lexeme.getType() == Lexeme.Type.CLOSE_PARENTHESIS)
				{
					return expression;
				}
				else
				{
					throw new ExpressionParserException("Unexpected token");
				}
			default:
				throw new ExpressionParserException("Unexpected token");
		}
	}
}
