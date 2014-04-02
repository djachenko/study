package ru.nsu.fit.djachenko.mtk.translator.ariphmetics.tree;

public class Variable implements TreeNode
{
	private final String name;

	public Variable(String name)
	{
		this.name = name;
	}

	@Override
	public String representation()
	{
		return name;
	}
}
