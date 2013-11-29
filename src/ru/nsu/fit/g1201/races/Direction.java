package ru.nsu.fit.g1201.races;

public enum Direction
{
	LEFT(-1, 0),
	RIGHT(1, 0),
	FORWARD(0, 1);

	private int dx;
	private int dy;

	Direction(int dx, int dy)
	{
		this.dx = dx;
		this.dy = dy;
	}

	public int getDx()
	{
		return dx;
	}

	public int getDy()
	{
		return dy;
	}
}
