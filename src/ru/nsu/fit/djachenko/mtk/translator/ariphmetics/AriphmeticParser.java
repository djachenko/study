package ru.nsu.fit.djachenko.mtk.translator.ariphmetics;

import ru.nsu.fit.djachenko.mtk.translator.ariphmetics.tree.*;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexeme;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;

import java.io.IOException;

public class AriphmeticParser
{
	private final Lexer lexer;

	public AriphmeticParser(Lexer lexer)
	{
		this.lexer = lexer;
	}

	TreeNode parseExpression() throws IOException, LexerException, AriphmeticParserException
	{
		TreeNode root = parseTerm();

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

	private TreeNode parseTerm() throws IOException, LexerException, AriphmeticParserException
	{
		TreeNode root = parseFactor();

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

	private TreeNode parseFactor() throws IOException, LexerException, AriphmeticParserException
	{
		TreeNode root = parsePower();

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

	private TreeNode parsePower() throws IOException, LexerException, AriphmeticParserException
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

	private TreeNode parseAtom() throws IOException, LexerException, AriphmeticParserException
	{
		Lexeme lexeme = lexer.getLexeme();

		switch (lexeme.getType())
		{
			case VALUE:
				return new Value(lexeme.getValue());
			case IDENTIFIER:
				return new Variable(lexeme.getValue());
			case OPEN_PARENTHESIS:
				TreeNode expression = parseExpression();

				lexeme = lexer.getLexeme();

				if (lexeme.getType() == Lexeme.Type.CLOSE_PARENTHESIS)
				{
					return expression;
				}
				else
				{
					throw new AriphmeticParserException("Unexpected token");
				}
			default:
				throw new AriphmeticParserException("Unexpected token");
		}
	}
}
