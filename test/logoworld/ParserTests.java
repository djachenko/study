package logoworld;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import logoworld.Parser;

import java.util.Scanner;

public class ParserTests
{
	static private Parser parser = null;
	static private Scanner expected = null;

	@Before
	public static void prepare()
	{
		parser = new Parser("logoworldtests/TestProgram.lw");
		expected = new Scanner("logoworldtests/TestProgram.lw");
	}

	@Test
	public void GetCommand()
	{
		while (parser.ready())
		{
			Assert.assertArrayEquals(expected.nextLine().replaceAll("\\s+", " ").trim().split(" "), parser.getCommand());
		}
	}
}
