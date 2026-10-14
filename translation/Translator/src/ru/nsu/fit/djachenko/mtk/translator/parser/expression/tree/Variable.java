package ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public class Variable implements Expression
{
	private final Type type;
	private final String name;
	private final String index;

	public Variable(Type type, String name, int index)
	{
		this.type = type;
		this.name = name;
		this.index = String.valueOf(index);
	}

	@Override
	public Type getType()
	{
		return type;
	}

	@Override
	public double count()
	{
		return 0;
	}

	@Override
	public String toCode()
	{
		return "dload " + getIndex() + '\n';
	}

	public String getName()
	{
		return name;
	}

	public String getIndex()
	{
		return index;
	}
}
