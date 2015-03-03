package ru.nsu.fit.djachenko.mtk.translator.parser;

public enum Type
{
	DOUBLE("D")
		{
			@Override
			public boolean isCastableTo(Type otherType)
			{
				return otherType == DOUBLE;
			}
		},
	INT("D")
		{
			@Override
			public boolean isCastableTo(Type otherType)
			{
				return otherType != VOID;
			}
		},
	VOID("V")
		{
			@Override
			public boolean isCastableTo(Type otherType)
			{
				return otherType == VOID;
			}
		},
	BOOLEAN("B")
		{
			@Override
			public boolean isCastableTo(Type otherType)
			{
				return otherType == BOOLEAN;
			}
		};

	private final String representation;

	Type(String representation)
	{
		this.representation = representation;
	}

	public static Type getType(String name)
	{
		return Type.valueOf(name.toUpperCase());
	}

	@Override
	public String toString()
	{
		return representation;
	}

	public static Type common(Type a, Type b)
	{
		if (a == VOID || b == VOID)
		{
			throw new RuntimeException();
		}

		if (a == DOUBLE || b == DOUBLE)
		{
			return DOUBLE;
		}
		else
		{
			return INT;
		}
	}

	public abstract boolean isCastableTo(Type otherType);
}
