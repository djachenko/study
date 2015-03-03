package ru.nsu.fit.djachenko.mtk.translator.lexer;

import org.junit.Assert;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import ru.nsu.fit.djachenko.mtk.translator.buffer.Buffer;

import java.io.IOException;
import java.io.StringReader;
import java.util.Map;

public class LexerTest
{
	@Rule
	public final ExpectedException expectedException = ExpectedException.none();

	@Test
	public void testEmptyString() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("")));

		Assert.assertEquals(Lexeme.Type.END_OF_PROGRAM, lexer.getLexeme().getType());
	}

	@Test
	public void testMultilineComments() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("/*blabla*/")));

		Lexeme lexeme = lexer.getLexeme();

		Assert.assertEquals(Lexeme.Type.END_OF_PROGRAM, lexeme.getType());
	}

	@Test
	public void testEnclosedMultilineComments() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("/*bl/*abla*/")));

		Lexeme lexeme = lexer.getLexeme();

		Assert.assertEquals(Lexeme.Type.END_OF_PROGRAM, lexeme.getType());
	}

	@Test
	public void testNotClosedMultilineComments() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("/*bl/*abl")));

		expectedException.expect(LexerException.class);

		lexer.getLexeme();
	}

	@Test
	public void testOneLineComments() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("//comment\n10")));

		Lexeme lexeme = lexer.getLexeme();
		Assert.assertEquals(Lexeme.Type.VALUE, lexeme.getType());
		lexeme = lexer.getLexeme();
		Assert.assertEquals(Lexeme.Type.END_OF_PROGRAM, lexeme.getType());
	}

	@Test
	public void testOneLineCommentsInTheEnd() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("//comment")));

		Lexeme lexeme = lexer.getLexeme();
		Assert.assertEquals(Lexeme.Type.END_OF_PROGRAM, lexeme.getType());
	}

	@Test
	public void testSimpleLexemes() throws IOException, LexerException
	{
		Map<Integer, Lexeme.Type> simpleLexemes = Lexeme.getSimpleLexemes();

		Lexer lexer;

		for (int lexeme : simpleLexemes.keySet())
		{
			lexer = new Lexer(new Buffer(new StringReader(String.valueOf((char)lexeme))));

			Lexeme result = lexer.getLexeme();

			Assert.assertEquals(simpleLexemes.get(lexeme), result.getType());
			if (lexeme != Buffer.EOP)
			{
				Assert.assertEquals(Lexeme.Type.END_OF_PROGRAM, lexer.getLexeme().getType());
			}
		}
	}

	@Test
	public void rejectTest() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("")));

		Lexeme first = lexer.getLexeme();

		lexer.reject();

		Lexeme second = lexer.getLexeme();

		Assert.assertSame(first, second);
	}

	@Test
	public void rejectExceptionTest() throws IOException, LexerException
	{
		Lexer lexer = new Lexer(new Buffer(new StringReader("")));

		expectedException.expect(LexerException.class);

		lexer.reject();
	}
}
