package ru.nsu.fit.djachenko.javaperfomance.сфы;

import java.util.concurrent.atomic.AtomicInteger;

public class Atomic extends ConcurrentIncrementable
{
	private AtomicInteger count = new AtomicInteger();

	@Override
	public void increment()
	{
		count.incrementAndGet();
	}

	@Override
	public int getCount()
	{
		return count.get();
	}
}
