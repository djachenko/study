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

	public ExpressionParser(Lexer lexer)
	{
		this.lexer = lexer;
	}

	public Expression parseExpression(Map<String, Variable> variableMap) throws IOException, LexerException, ExpressionParserException
	{
		Expression root = parseTerm(variableMap);

		while (!lexer.programEnded())
		{
			Lexeme currentLexeme = lexer.getLexeme();

			switch (currentLexeme.getType())
			{
				case PLUS:
					root = new Sum(root, parseTerm(variableMap));
					break;
				case MINUS:
					root = new Sub(root, parseTerm(variableMap));
					break;
				default:
					lexer.reject();
					return root;
			}
		}

		return root;
	}

	private Expression parseTerm(Map<String, Variable> variableMap) throws IOException, LexerException, ExpressionParserException
	{
		Expression root = parseFactor(variableMap);

		while (!lexer.programEnded())
		{
			Lexeme currentLexeme = lexer.getLexeme();

			switch (currentLexeme.getType())
			{
				case MULTIPLY:
					root = new Mul(root, parseFactor(variableMap));
					break;
				case DIVIDE:
					root = new Div(root, parseFactor(variableMap));
					break;
				default:
					lexer.reject();
					return root;
			}
		}

		return root;
	}

	private Expression parseFactor(Map<String, Variable> variableMap) throws IOException, LexerException, ExpressionParserException
	{
		Expression root = parsePower(variableMap);

		while (!lexer.programEnded())
		{
			Lexeme currentLexeme = lexer.getLexeme();

			switch (currentLexeme.getType())
			{
				case POWER:
					root = new Power(root, parseFactor(variableMap));
					break;
				default:
					lexer.reject();
					return root;
			}
		}

		return root;
	}

	private Expression parsePower(Map<String, Variable> variableMap) throws IOException, LexerException, ExpressionParserException
	{
		Lexeme currentLexeme = lexer.getLexeme();

		switch (currentLexeme.getType())
		{
			case MINUS:
				return new UnaryMinus(parsePower(variableMap));
			default:
				lexer.reject();
				return parseAtom(variableMap);
		}
	}

	private Expression parseAtom(Map<String, Variable> variableMap) throws IOException, LexerException, ExpressionParserException
	{
		Lexeme lexeme = lexer.getLexeme();

		switch (lexeme.getType())
		{
			case VALUE:
				return new Constant(lexeme.getValue());
			case IDENTIFIER:
				return variableMap.get(lexeme.getValue());
			case OPEN_PARENTHESIS:
				Expression expression = parseExpression(variableMap);

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
				System.out.println(lexeme.getType());
				System.out.println(lexeme.getValue());
				throw new ExpressionParserException("Unexpected token");
		}
	}
}
