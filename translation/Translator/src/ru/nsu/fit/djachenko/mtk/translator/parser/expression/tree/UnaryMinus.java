package ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public class UnaryMinus implements Expression
{
	private final Expression argument;

	public UnaryMinus(Expression argument)
	{
		this.argument = argument;
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
		return argument.toCode() + "dneg\n";
	}

	@Override
	public Type getType()
	{
		return argument.getType();
	}
}
