package ru.nsu.fit.djachenko.mtk.translator.parser.logic;

import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexeme;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.ExpressionParser;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.ExpressionParserException;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Expression;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Variable;

import java.io.IOException;
import java.util.Map;

public class LogicExpressionParser
{
	private final ExpressionParser expressionParser;
	private final Lexer lexer;

	public LogicExpressionParser(ExpressionParser expressionParser, Lexer lexer)
	{
		this.expressionParser = expressionParser;
		this.lexer = lexer;
	}

	public LogicExpression parseLogicExpression(Map<String, Variable> variableMap) throws ExpressionParserException, IOException, LexerException
	{
		Expression left = expressionParser.parseExpression(variableMap);

		Lexeme sign = lexer.getLexeme();

		Expression right = expressionParser.parseExpression(variableMap);

		switch (sign.getType())
		{
			case LESS:
				return new Less(left, right);
			case MORE:
				return new More(left, right);
			case EQUAL:
				return new Equal(left, right);
			default:
				throw new RuntimeException();
		}
	}
}
