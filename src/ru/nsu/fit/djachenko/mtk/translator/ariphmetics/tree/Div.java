package ru.nsu.fit.djachenko.mtk.translator.ariphmetics.tree;

public class Div implements TreeNode
{
	private final TreeNode left;
	private final TreeNode right;

	public Div(TreeNode left, TreeNode right)
	{
		this.left = left;
		this.right = right;
	}

	@Override
	public String representation()
	{
		return left.representation() + " / " + right.representation();
	}
}
