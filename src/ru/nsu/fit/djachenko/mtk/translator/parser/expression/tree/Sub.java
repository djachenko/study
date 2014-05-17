package ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public class Sub implements Expression
{
	private final Expression left;
	private final Expression right;
	private final Type type;

	public Sub(Expression left, Expression right)
	{
		this.left = left;
		this.right = right;
		this.type = Type.common(left.getType(), right.getType());
	}

	@Override
	public String toString()
	{
		return left.toString() + " - " + right.toString();
	}

	@Override
	public double count()
	{
		return left.count() - right.count();
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
