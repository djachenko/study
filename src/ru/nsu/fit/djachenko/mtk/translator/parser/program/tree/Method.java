package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Variable;

import java.util.List;

public class Method extends Variable
{
	private final List<Parameter> parameters;
	private final List<Statement> body;

	public Method(Type returnType, String name, List<Parameter> parameters, List<Statement> body)
	{
		super(returnType, name, -1);

		this.parameters = parameters;
		this.body = body;
	}

	@Override
	public String toCode()
	{
		StringBuilder builder = new StringBuilder();

		builder.append(".method public static ")
		       .append(getName())
		       .append('(');

		for (Parameter parameter : parameters)
		{
			builder.append(parameter)
			       .append(';');
		}

		builder.append(')')
		       .append(getType())
		       .append('\n');

		builder.append(".limit stack 100\n")
		       .append(".limit locals ")
		       .append(20)
		       .append('\n');

		for (Statement statement : body)
		{
			builder.append(statement.toCode());
		}

		builder.append(".end method\n");

		return builder.toString();
	}

	@Override
	public String toString()
	{
		return toCode();
	}
}
