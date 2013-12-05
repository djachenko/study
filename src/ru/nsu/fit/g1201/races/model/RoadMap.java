package ru.nsu.fit.g1201.races.model;

public abstract class RoadMap
{
	abstract int width();
	abstract RoadLine nextLine();

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
