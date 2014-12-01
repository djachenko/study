package ru.nsu.fit.djachenko.javaperfomance.сфы;

public abstract class ConcurrentIncrementable
{
	private int count;

	public abstract void increment();

	protected void inc()
	{
		count++;
	}

	public int getCount()
	{
		return count;
	}
}
