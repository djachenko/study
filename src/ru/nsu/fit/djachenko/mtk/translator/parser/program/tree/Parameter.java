package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public class Parameter implements Statement {
	private final Type type;

	public Parameter(Type type)
	{
		this.type = type;
	}

	@Override
	public String toString()
	{
		switch (type)
		{
			case INT:
			case DOUBLE:
				return "D";
			case VOID:
				return "V";
			default:
				throw new RuntimeException();
		}
	}

	@Override
	public String toCode()
	{
		return "";
	}

	@Override
	public Type getType()
	{
		return Type.VOID;
	}

	@Override
	public int getLocalCount()
	{
		return 1;
	}
}
