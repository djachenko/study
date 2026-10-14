package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.logic.LogicExpression;

public class IfElse implements Statement
{
	private final LogicExpression condition;
	private final Statement ifBody;
	private final Statement elseBody;
	private final int index;

	public IfElse(LogicExpression condition, Statement ifBody, Statement elseBody, int index)
	{
		this.condition = condition;
		this.ifBody = ifBody;
		this.elseBody = elseBody;
		this.index = index;
	}

	@Override
	public String toCode()
	{
		return condition.toCode() +
		       " IfStart" +
		       index +
		       '\n' +
		       "goto IfEnd" +
		       index +
		       "\nIfStart" +
		       index +
		       ":\n" +
		       ifBody.toCode() +
		       "goto ElseEnd" +
		       index +
		       "\nIfEnd" +
		       index +
		       ":\n" +
		       elseBody.toCode() +
		       "ElseEnd" +
		       index +
		       ":\n";
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
