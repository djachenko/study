package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.*;

import java.util.List;

public class Call implements Statement, Expression
{
	private final Method method;
	private final List<Variable> parameters;

	public Call(Method method, List<Variable> parameters)
	{
		this.method = method;
		this.parameters = parameters;
	}

	@Override
	public double count()
	{
		return 0;
	}

	@Override
	public String toCode()
	{
		StringBuilder builder = new StringBuilder();

		for (Variable parameter : parameters)
		{
			builder.append(parameter.toCode());
		}

		builder.append("invokestatic ")
		       .append(Program.CLASSNAME)
		       .append(".")
		       .append(method.getName())
		       .append("(D)")
		       .append(method.getType())
		       .append('\n');

		return builder.toString();
	}

	@Override
	public Type getType()
	{
		return method.getType();
	}
}
