package ru.nsu.fit.djachenko.mtk.translator.ariphmetics.tree;

public class Value implements TreeNode
{
	private final String value;

	public Value(String value)
	{
		this.value = value;
	}

	@Override
	public String representation()
	{
		return value;
	}
}
