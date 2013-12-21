package ru.nsu.fit.g1201.races.model.roadmaps;

import ru.nsu.fit.g1201.races.model.Barrier;
import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.model.RoadLine;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Random;

public class RandomRoadMap extends RoadMap
{
	private static final int WIDTH = 9;

	private RoadLine line = new RoadLine(WIDTH);

	private LinkedList<Barrier> barriers = new LinkedList<>();

	private int lineCount = 0;

	private Random random = new Random(System.currentTimeMillis());

	RandomRoadMap(Race race)
	{
		super(race);
	}

	@Override
	public int width()
	{
		return WIDTH;
	}

	@Override
	public RoadLine nextLine()
	{
		if (lineCount % 10 == 0 && lineCount >= 15)
		{
			createBarrier();
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

	private void createBarrier()
	{
		barriers.add(new Barrier(random.nextInt(width() - 1), lineCount, 2, 2, getRace()));
	}
}
