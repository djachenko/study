package ru.nsu.fit.djachenko.mtk.translator.ariphmetics.tree;

public class UnaryMinus implements TreeNode
{
	private final TreeNode argument;

	public UnaryMinus(TreeNode argument)
	{
		this.argument = argument;
	}

	@Override
	public String representation()
	{
		return "-" + argument.representation();
	}
}
