package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Expression;

public class Return implements Statement
{
	private final Expression value;

	public Return()
	{
		value = null;
	}

	public Return(Expression value)
	{
		this.value = value;
	}

	@Override
	public String toCode()
	{
		if (value != null)
		{
			return value.toCode() + "dreturn\n";
		}
		else
		{
			return "return\n";
		}
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
