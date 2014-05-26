package ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public class Mul implements Expression
{
	private final Expression left;
	private final Expression right;
	private final Type type;

	public Mul(Expression left, Expression right)
	{
		this.left = left;
		this.right = right;
		this.type = Type.common(left.getType(), right.getType());
	}

	@Override
	public String toString()
	{
		return left.toString() + " * " + right.toString();
	}

	@Override
	public double count()
	{
		return left.count() * right.count();
	}

	@Override
	public String toCode()
	{
		return left.toCode() + right.toCode() + "dmul\n";
	}

	@Override
	public Type getType()
	{
		return type;
	}
}
