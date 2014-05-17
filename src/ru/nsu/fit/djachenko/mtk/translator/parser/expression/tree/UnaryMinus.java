package ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public class UnaryMinus implements Expression
{
	private final Expression argument;
	private final Type type;

	public UnaryMinus(Expression argument)
	{
		this.argument = argument;
		this.type = argument.getType();
	}

	@Override
	public String toString()
	{
		return "-" + argument.toString();
	}

	@Override
	public double count()
	{
		return - argument.count();
	}

	@Override
	public String toCode()
	{
		return null;
	}

	@Override
	public Type getType()
	{
		return type;
	}
}
