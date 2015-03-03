package ru.nsu.fit.djachenko.pusher.model;

public enum  Direction
{
	LEFT(-1, 0),
	RIGHT(1, 0),
	DOWN(0, 1),//y axis is down-directed
	UP(0, -1);//y axis is down-directed

	private int dx;
	private int dy;

	private Direction(int x, int y)
	{
		dx = x;
		dy = y;
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
