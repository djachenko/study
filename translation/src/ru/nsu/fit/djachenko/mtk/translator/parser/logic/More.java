package ru.nsu.fit.djachenko.mtk.translator.parser.logic;

import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Expression;

public class More implements LogicExpression
{
	private final Less invert;

	public More(Expression left, Expression right)
	{
		invert = new Less(right, left);
	}

	@Override
	public String toCode()
	{
		return invert.toCode();
	}
}
