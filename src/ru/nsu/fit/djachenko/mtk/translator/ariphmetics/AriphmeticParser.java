package ru.nsu.fit.djachenko.mtk.translator.ariphmetics;

import ru.nsu.fit.djachenko.mtk.translator.ariphmetics.tree.*;
import ru.nsu.fit.djachenko.mtk.translator.buffer.BufferException;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexeme;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;

import java.io.IOException;

public class AriphmeticParser
{
	private final Lexer lexer;

	private Lexeme lexeme;

	public AriphmeticParser(Lexer lexer)
	{
		this.lexer = lexer;
	}

	TreeNode parseExpression() throws BufferException, IOException, LexerException, AriphmeticParserException
	{
		TreeNode root = parseTerm();

		while (!lexer.programEnded())
		{
			//lexeme = lexer.getLexeme();

			switch (lexeme.getType())
			{
				case PLUS:
					root = new Sum(root, parseTerm());
					break;
				case MINUS:
					root = new Sub(root, parseTerm());
					break;
				default:
					return root;
			}
		}

		return root;
	}

	private TreeNode parseTerm() throws LexerException, IOException, BufferException, AriphmeticParserException
	{
		TreeNode root = parseFactor();

		while (!lexer.programEnded())
		{
			lexeme = lexer.getLexeme();//because there isn't getLexeme() in parseFactor

			switch (lexeme.getType())
			{
				case MULTIPLY:
					root = new Mul(root, parseFactor());
					break;
				case DIVIDE:
					root = new Div(root, parseFactor());
					break;
				default:
					return root;
			}
		}

		return root;
	}

	private TreeNode parseFactor() throws BufferException, IOException, LexerException, AriphmeticParserException
	{
		return parsePower();
	}

	private TreeNode parsePower() throws LexerException, IOException, BufferException, AriphmeticParserException
	{
		Lexeme current = lexer.getLexeme();

		switch (current.getType())
		{
			case MINUS:
				return new UnaryMinus(parsePower());
			default:
				lexeme = current;
				return parseAtom();
		}
	}

	private TreeNode parseAtom() throws BufferException, IOException, LexerException, AriphmeticParserException
	{
		switch (lexeme.getType())
		{
			case VALUE:
				return new Value(lexeme.getValue());
			case IDENTIFIER:
				return new Variable(lexeme.getValue());
			case OPEN_PARENTHESIS:
				return parseExpression();
		}

		throw new IllegalArgumentException();
	}
}
