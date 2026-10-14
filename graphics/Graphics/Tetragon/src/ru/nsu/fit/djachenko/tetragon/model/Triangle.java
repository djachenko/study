package ru.nsu.fit.djachenko.tetragon.model;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;

public class Triangle
{
	private final List<Point2D.Double> points = new ArrayList<>(3);
	private final List<Point2D.Double> mappings = new ArrayList<>(3);

	Triangle(Point2D.Double[] points, Point2D.Double[] mappings)
	{
		for (int i = 0; i < points.length; i++)
		{
			this.points.add(points[i]);
			this.mappings.add(mappings[i]);
		}
	}

	public List<Point2D.Double> getPoints()
	{
		return points;
	}

	public List<Point2D.Double> getMappings()
	{
		return mappings;
	}
}
