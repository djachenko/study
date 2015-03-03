package ru.nsu.fit.djachenko.tetragon.model;

import ru.nsu.fit.djachenko.tetragon.Functions;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

public class Tetragon
{
	private final List<Point2D.Double> points = new ArrayList<>();

	private final Triangle a;
	private final Triangle b;

	private final Function<Point2D.Double, Point2D.Double> aMapper;
	private final Function<Point2D.Double, Point2D.Double> bMapper;

	public Tetragon(Point2D.Double a, Point2D.Double b, Point2D.Double c, Point2D.Double d)
	{
		points.add(a);
		points.add(b);
		points.add(c);
		points.add(d);

		if (!Functions.intersectRay(b, d, a, c))
		{
			this.a = new Triangle(new Point2D.Double[]{c, a, b}, new Point2D.Double[]{new Point2D.Double(1, 1),
			                                                                          new Point2D.Double(0, 0),
			                                                                          new Point2D.Double(1, 0)});

			this.b = new Triangle(new Point2D.Double[]{a, d, c}, new Point2D.Double[]{new Point2D.Double(0, 0),
			                                                                          new Point2D.Double(0, 1),
			                                                                          new Point2D.Double(1, 1)});
		}
		else
		{
			this.a = new Triangle(new Point2D.Double[]{a, b, d}, new Point2D.Double[]{new Point2D.Double(0, 0),
			                                                                          new Point2D.Double(1, 0),
			                                                                          new Point2D.Double(0, 1)});

			this.b = new Triangle(new Point2D.Double[]{d, c, b}, new Point2D.Double[]{new Point2D.Double(0, 1),
			                                                                          new Point2D.Double(1, 1),
			                                                                          new Point2D.Double(1, 0)});
		}

		if (isConvex())
		{
			aMapper = new TetragonMapper(this);
			bMapper = aMapper;
		}
		else
		{
			aMapper = new TriangleMapper(this.a);
			bMapper = new TriangleMapper(this.b);
		}
	}

	public List<Point2D.Double> getPoints()
	{
		return points;
	}

	public Triangle getA()
	{
		return a;
	}

	public Triangle getB()
	{
		return b;
	}

	public Function<Point2D.Double, Point2D.Double> getAMapper()
	{
		return aMapper;
	}

	public Function<Point2D.Double, Point2D.Double> getBMapper()
	{
		return bMapper;
	}

	public boolean isConvex()
	{
		return Functions.intersect(points.get(0), points.get(2), points.get(1), points.get(3));
	}

	public boolean isComplex()
	{
		return Functions.intersect(points.get(0), points.get(1), points.get(2), points.get(3)) ||
		       Functions.intersect(points.get(1), points.get(2), points.get(3), points.get(0));
	}
}
