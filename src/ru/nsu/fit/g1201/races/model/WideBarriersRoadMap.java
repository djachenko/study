package ru.nsu.fit.g1201.races.model;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Random;

public class WideBarriersRoadMap extends RoadMap
{
	private static final int WIDTH = 9;

	private RoadLine line = new RoadLine(WIDTH);

	private LinkedList<Barrier> barriers = new LinkedList<>();

	private int lineCount = 0;

	private Random random = new Random(System.currentTimeMillis());

	WideBarriersRoadMap(Race race)
	{
		super(race);
	}

	@Override
	int width()
	{
		return WIDTH;
	}

	@Override
	RoadLine nextLine()
	{
		if (lineCount % 10 == 0 && lineCount >= 15)
		{
			createBarriers();
		}

		RoadLine result = line.clone();

		for (Iterator<Barrier> i = barriers.iterator(); i.hasNext(); )
		{
			Barrier barrier = i.next();

			barrier.draw(result, lineCount);

			if (barrier.isAlreadyDrawn(lineCount))
			{
				i.remove();
			}
		}

		lineCount++;

		return result;
	}

	private void createBarriers()
	{
		int free = random.nextInt(width() - 2) + 1;

		for (int x = 0; x < WIDTH; x++)
		{
			if (Math.abs(x - free) > 1)
			{
				System.out.println("barr " + x);
				barriers.add(new Barrier(x, lineCount, 1, 2, getRace()));
			}
		}
	}
}
