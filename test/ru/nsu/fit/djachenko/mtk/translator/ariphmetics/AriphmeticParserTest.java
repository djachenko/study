package ru.nsu.fit.djachenko.mtk.translator.ariphmetics;


import org.junit.Assert;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import ru.nsu.fit.djachenko.mtk.translator.buffer.Buffer;
import ru.nsu.fit.djachenko.mtk.translator.buffer.BufferException;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;

import java.io.IOException;
import java.io.StringReader;

public class AriphmeticParserTest
{
	@Rule
	public ExpectedException expectedException = ExpectedException.none();

	@Test
	public void parseNumberTest() throws LexerException, IOException, BufferException, AriphmeticParserException
	{
		AriphmeticParser parser = new AriphmeticParser(new Lexer(new Buffer(new StringReader("10"))));

		Assert.assertEquals(String.valueOf(10), parser.parseExpression().representation());
	}

	@Test
	public void parseSumTest() throws LexerException, IOException, BufferException, AriphmeticParserException
	{
		AriphmeticParser parser = new AriphmeticParser(new Lexer(new Buffer(new StringReader("10+11+1"))));

		Assert.assertEquals("10 + 11 + 1", parser.parseExpression().representation());
	}

	@Test
	public void parseSubTest() throws LexerException, IOException, BufferException, AriphmeticParserException
	{
		AriphmeticParser parser = new AriphmeticParser(new Lexer(new Buffer(new StringReader("10-11"))));

		Assert.assertEquals("10 - 11", parser.parseExpression().representation());
	}

	@Test
	public void parseMulTest() throws LexerException, IOException, BufferException, AriphmeticParserException
	{
		AriphmeticParser parser = new AriphmeticParser(new Lexer(new Buffer(new StringReader("10-11*15"))));

		Assert.assertEquals("10 - 11 * 15", parser.parseExpression().representation());
	}


}
