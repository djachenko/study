package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Variable;

import java.util.List;

public class Method extends Variable
{
	private final Statement body;
	private final String signature;
	private final int localCount;

	public Method(Type returnType, String name, List<Parameter> parameters, Statement body)
	{
		super(returnType, name, -1);

		this.body = body;
		this.localCount = body == null ? 0 : body.getLocalCount() * 2;

		StringBuilder builder = new StringBuilder();

		builder.append(name).append('(');

		parameters.forEach(builder::append);

		builder.append(')').append(returnType);

		this.signature = builder.toString();
	}

	@Override
	public String toCode()
	{
		return ".method public static " +
		       signature +
		       '\n' +
		       ".limit stack 100\n" +
		       ".limit locals " +
		       localCount +
		       '\n' +
		       body.toCode() +
		       "return\n" +
		       ".end method\n";
	}

	@Override
	public String toString()
	{
		return toCode();
	}

	public String getSignature()
	{
		return signature;
	}
}
