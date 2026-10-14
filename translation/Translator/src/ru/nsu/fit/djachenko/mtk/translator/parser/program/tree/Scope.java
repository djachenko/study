package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

import java.util.List;

public class Scope implements Statement
{
	private final List<Statement> statements;
	private final int localCount;

	public Scope(List<Statement> statements, int localCount)
	{
		this.statements = statements;
		this.localCount = localCount;
	}

	@Override
	public String toCode()
	{
		final StringBuilder builder = new StringBuilder();

		statements.forEach(statement -> builder.append(statement.toCode()));

		return builder.toString();
	}

	@Override
	public Type getType()
	{
		return Type.VOID;
	}

	@Override
	public int getLocalCount()
	{
		for (Statement statement : statements)
		{
			System.out.println(statement.getClass() + " " + statement.getLocalCount());
		}

		return Math.max(statements.stream().map(Statement::getLocalCount).reduce(Math::max).get(), localCount);
	}
}
