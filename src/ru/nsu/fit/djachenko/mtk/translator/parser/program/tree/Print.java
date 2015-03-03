package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

import java.util.Arrays;

public class Print extends Method
{
	public Print()
	{
		super(Type.VOID, "print", Arrays.asList(new Parameter(Type.DOUBLE)), null);
	}

	@Override
	public String toCode()
	{
		return ".method public static print(D)V\n" +
		".limit locals 5\n" +
		".limit stack 5\n" +
		"getstatic java/lang/System/out Ljava/io/PrintStream;\n" +
		"dload_0\n" +
		"invokevirtual java/io/PrintStream/println(D)V\n" +
		"return\n" +
		".end method\n";
	}
}
