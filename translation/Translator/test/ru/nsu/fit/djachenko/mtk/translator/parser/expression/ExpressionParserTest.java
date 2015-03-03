package ru.nsu.fit.djachenko.mtk.translator.parser.expression;


import org.junit.Assert;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Expression;
import ru.nsu.fit.djachenko.mtk.translator.buffer.Buffer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Variable;

import java.io.IOException;
import java.io.StringReader;
import java.util.Map;
import java.util.Random;

public class ExpressionParserTest
{
	@Rule
	public ExpectedException expectedException = ExpectedException.none();

	private double[] firstArguments;
	private double[] secondArguments;

	private static final int SIZE = 32;
	private static final double EPSILON = 0.001;

	private final Map<String, Variable> variableMap = null;

	@Before
	public void prepare()
	{
		Random random = new Random(System.currentTimeMillis());

		firstArguments = new double[SIZE];
		secondArguments = new double[SIZE];

		for (int i = 0; i < SIZE; i++)
		{
			firstArguments[i] = Math.sqrt(random.nextDouble());
			secondArguments[i] = Math.sqrt(random.nextDouble());
		}
	}

	@Test
	public void parseValueTest() throws LexerException, IOException, ExpressionParserException
	{
		for (double x : firstArguments)
		{
			ExpressionParser parser = new ExpressionParser(new Lexer(new Buffer(new StringReader(String.valueOf(x)))));

			Expression tree = parser.parseExpression(variableMap);

			Assert.assertEquals(x, tree.count(), EPSILON);
		}
	}

	@Test
	public void parseSumTest() throws LexerException, ExpressionParserException, IOException
	{
		for (int i = 0; i < firstArguments.length; i++)
		{
			String expression = String.valueOf(firstArguments[i]) + "+" + String.valueOf(secondArguments[i]);

			ExpressionParser parser = new ExpressionParser(new Lexer(new Buffer(new StringReader(expression))));

			Assert.assertEquals(firstArguments[i] + secondArguments[i], parser.parseExpression(variableMap).count(), EPSILON);
		}
	}

	@Test
	public void parseSubTest() throws LexerException, IOException, ExpressionParserException
	{
		for (int i = 0; i < firstArguments.length; i++)
		{
			String expression = String.valueOf(firstArguments[i]) + "-" + String.valueOf(secondArguments[i]);

			ExpressionParser parser = new ExpressionParser(new Lexer(new Buffer(new StringReader(expression))));

			Assert.assertEquals(firstArguments[i] - secondArguments[i], parser.parseExpression(variableMap).count(), EPSILON);
		}
	}

	@Test
	public void parseMulTest() throws LexerException, IOException, ExpressionParserException
	{
		for (int i = 0; i < firstArguments.length; i++)
		{
			String expression = String.valueOf(firstArguments[i]) + "*" + String.valueOf(secondArguments[i]);

			ExpressionParser parser = new ExpressionParser(new Lexer(new Buffer(new StringReader(expression))));

			Assert.assertEquals(firstArguments[i] * secondArguments[i], parser.parseExpression(variableMap).count(), EPSILON);
		}
	}

	@Test
	public void parseDivTest() throws LexerException, IOException, ExpressionParserException
	{
		for (int i = 0; i < firstArguments.length; i++)
		{
			String expression = String.valueOf(firstArguments[i]) + "/" + String.valueOf(secondArguments[i]);

			ExpressionParser parser = new ExpressionParser(new Lexer(new Buffer(new StringReader(expression))));

			Assert.assertEquals(firstArguments[i] / secondArguments[i], parser.parseExpression(variableMap).count(), EPSILON);
		}
	}

	@Test
	public void parseUnaryMinusTest() throws LexerException, IOException, ExpressionParserException
	{
		for (double x : firstArguments)
		{
			String expression = String.valueOf("-" + x);

			ExpressionParser parser = new ExpressionParser(new Lexer(new Buffer(new StringReader(expression))));

			Assert.assertEquals(-1 * x, parser.parseExpression(variableMap).count(), EPSILON);
		}
	}

	@Test
	public void parseMultipleUnaryMinusTest() throws LexerException, IOException, ExpressionParserException
	{
		StringBuilder builder = new StringBuilder();

		for (double x : firstArguments)
		{
			for (int length = 0; length < 10; length++)
			{
				builder.setLength(0);

				for (int i = 0; i < length; i++)
				{
					builder.append('-');
				}

				String expression = builder.append(x).toString();

				ExpressionParser parser = new ExpressionParser(new Lexer(new Buffer(new StringReader(expression))));

				if (length % 2 == 0)
				{
					Assert.assertEquals(x, parser.parseExpression(variableMap).count(), EPSILON);
				}
				else
				{
					Assert.assertEquals(-x, parser.parseExpression(variableMap).count(), EPSILON);
				}
			}
		}
	}
}
