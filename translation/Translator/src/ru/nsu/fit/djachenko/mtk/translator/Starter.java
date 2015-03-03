package ru.nsu.fit.djachenko.mtk.translator;

import ru.nsu.fit.djachenko.mtk.translator.buffer.Buffer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.ExpressionParserException;
import ru.nsu.fit.djachenko.mtk.translator.parser.program.ProgramParser;
import ru.nsu.fit.djachenko.mtk.translator.parser.program.ProgramParserException;
import ru.nsu.fit.djachenko.mtk.translator.parser.program.tree.Program;

import java.io.*;

public class Starter
{
	public static void main(String[] args) throws ProgramParserException
	{
		try (Reader reader = new FileReader("res/testprogram.myc"))
		{
			ProgramParser parser = new ProgramParser(new Lexer(new Buffer(reader)));

			Program program = parser.parseProgram();

			try (Writer writer = new FileWriter("res/testprogram.j"))
			{
				writer.append(program.toString());
				writer.flush();
			}
		}
		catch (IOException | LexerException | ExpressionParserException e)
		{
			e.printStackTrace();
		}
	}
}
