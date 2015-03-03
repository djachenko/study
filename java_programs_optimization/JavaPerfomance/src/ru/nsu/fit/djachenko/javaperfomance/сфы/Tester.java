package ru.nsu.fit.djachenko.javaperfomance.сфы;

import java.util.LinkedList;
import java.util.List;

public class Tester
{
	public static void main(String[] args) throws InterruptedException
	{
		int count = 1000000;
		int threadCount = 10;

		List<Thread> threads = new LinkedList<>();

		ConcurrentIncrementable incrementable = new UtilConcurrent();

		for (int i = 0; i < threadCount; i++)
		{
			Thread thread = new Thread(() -> {
				long start = System.currentTimeMillis();

				for (int j = 0; j < count; j++)
				{
					incrementable.increment();
				}

				long finish = System.currentTimeMillis();

				System.out.println(finish - start);
			});

			threads.add(thread);
			thread.start();
		}

		for (Thread thread : threads)
		{
			thread.join();
		}

		System.out.println(incrementable.getCount() + " " + count * threadCount);
	}
}
