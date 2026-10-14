package ru.nsu.fit.g1201.races.model.roadmaps;

import ru.nsu.fit.g1201.races.model.Race;
import ru.nsu.fit.g1201.races.model.RoadLine;

public abstract class RoadMap
{
	public abstract int width();
	public abstract RoadLine nextLine();

	private final Race race;

	RoadMap(Race race)
	{
		this.race = race;
	}

	protected Race getRace()
	{
		return race;
	}
}
