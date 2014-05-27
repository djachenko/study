package ru.nsu.fit.djachenko.mtk.translator.parser.logic;

import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Expression;

public class Less implements LogicExpression
{
	private final Expression left;
	private final Expression right;

	public Less(Expression left, Expression right)
	{
		this.left = left;
		this.right = right;
	}

	@Override
	public String toCode()
	{
		return left.toCode() + right.toCode() + "dcmpg\n" + "iflt";
	}
}
