package ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public class Constant implements Expression
{
	private final double value;
	private final Type type;

	public Constant(String value)
	{
		this.value = Double.valueOf(value);

		type = value.contains(".") ? Type.DOUBLE : Type.INT;
	}

	@Override
	public String toString()
	{
		return String.valueOf(value);
	}

	@Override
	public double count()
	{
		return value;
	}

	@Override
	public String toCode()
	{
		return "ldc2_w " + String.valueOf(value) + '\n';
	}

	@Override
	public Type getType()
	{
		return type;
	}
}
