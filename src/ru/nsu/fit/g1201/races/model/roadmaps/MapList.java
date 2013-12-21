package ru.nsu.fit.g1201.races.model.roadmaps;

import ru.nsu.fit.g1201.races.model.Race;

public class MapList
{
	private final static MapList instance = new MapList();
	private final String[] mapNames = new String[]
			{
					"Random",
					"WideBarriers"
			};

	private MapList()
	{}

	public static MapList getInstance()
	{
		return instance;
	}

	public String[] getMapNames()
	{
		return mapNames;
	}

	public RoadMap getRandomRoadMap(Race race)
	{
		return new RandomRoadMap(race);
	}

	public RoadMap getWideBarriersRoadMap(Race race)
	{
		return new WideBarriersRoadMap(race);
	}

	public RoadMap getRoadMap(int index, Race race)
	{
		switch (index)
		{
			case 0:
				return getRandomRoadMap(race);
			case 1:
				return getWideBarriersRoadMap(race);
			default:
				return null;
		}
	}
}
