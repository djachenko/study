package ru.nsu.fit.djachenko.javaperfomance.сфы;

public class Synchronized extends ConcurrentIncrementable
{
	@Override
	public void increment()
	{
		synchronized (this)
		{
			inc();
		}
	}
}
