package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.logic.LogicExpression;

public class If implements Statement
{
	private final LogicExpression condition;
	private final Statement body;
	private final int index;

	public If(LogicExpression condition, Statement body, int index)
	{
		this.condition = condition;
		this.body = body;
		this.index = index;
	}

	@Override
	public String toCode()
	{
		return condition.toCode() + "ifend" + index + "\n";
	}

	@Override
	public Type getType()
	{
		return Type.VOID;
	}

	@Override
	public int getLocalCount()
	{
		return 0;
	}
}
