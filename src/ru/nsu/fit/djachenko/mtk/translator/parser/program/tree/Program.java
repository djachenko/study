package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import java.util.List;

public class Program
{
	private final List<Method> methods;
	public static final String CLASSNAME = "defaultclass";

	public Program(List<Method> methods)
	{
		this.methods = methods;
	}

	public String toCode()
	{
		StringBuilder builder = new StringBuilder();

		builder.append(".class public " + CLASSNAME + "\n")
		       .append(".super java/lang/Object\n")
		       .append(".method public <init>()V\n")
		       .append("aload_0\n")
		       .append("invokespecial java/lang/Object/<init>()V\n")
		       .append("return\n")
		       .append(".end method\n\n");

		methods.forEach(method -> builder.append(method.toCode()).append('\n'));

		builder.append(".method public static main([Ljava/lang/String;)V\n" +
		               ".limit stack 5\n" +
		               ".limit locals 5\n" +
		               "invokestatic " + CLASSNAME + ".main()V\n" +
		               "return\n" +
		               ".end method");

		return builder.toString();
	}

	@Override
	public String toString()
	{
		return toCode();
	}
}
