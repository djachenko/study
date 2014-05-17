package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Expression;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Variable;

public class Assignment implements Statement {
	private final Variable variable;
	private final Expression value;

	public Assignment(Variable variable, Expression value)
	{
		this.variable = variable;
		this.value = value;
	}

	@Override
	public String toString()
	{
		return toCode();
	}

	@Override
	public String toCode()
	{
		return value.toCode() + "dstore " + variable.getIndex() + '\n';
	}

	@Override
	public Type getType()
	{
		return Type.VOID;
	}
}
