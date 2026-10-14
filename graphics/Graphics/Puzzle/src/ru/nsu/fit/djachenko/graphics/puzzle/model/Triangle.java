package ru.nsu.fit.djachenko.graphics.puzzle.model;

import java.awt.geom.Point2D;

public class Triangle
{
	private Point2D.Double[] vertices = new Point2D.Double[3];

	private Picture source;

	private Point2D.Double centroid;
	private final Point2D.Double initialPoint;

	private double alpha = 0;

	public Triangle(Point2D.Double point1, Point2D.Double point2, Point2D.Double point3, Picture source)
	{
		this.source = source;

		vertices[0] = point1;
		vertices[1] = point2;
		vertices[2] = point3;

		double centreX = 0;
		double centreY = 0;

		for (Point2D.Double point : vertices)
		{
			centreX += point.getX();
			centreY += point.getY();
		}

		centreX = (int)Math.round(1.0 * centreX / 3);
		centreY = (int)Math.round(1.0 * centreY / 3);

		centroid = new Point2D.Double(centreX, centreY);
		initialPoint = new Point2D.Double(centreX, centreY);
	}

	public void move(double x, double y)
	{
		double dx = x + initialPoint.getX() - centroid.getX();
		double dy = y + initialPoint.getY() - centroid.getY();

		for (Point2D.Double point : vertices)
		{
			point.setLocation(point.getX() + dx, point.getY() + dy);
		}

		centroid.setLocation(centroid.getX() + dx, centroid.getY() + dy);
	}

	public void turn(double phi)
	{
		double deltaPhi = phi - alpha;

		for (Point2D.Double point : vertices)
		{
			double x = point.getX() - centroid.getX();
			double y = point.getY() - centroid.getY();

			double xRes = x * Math.cos(deltaPhi) - y * Math.sin(deltaPhi) + centroid.getX();
			double yRes = x * Math.sin(deltaPhi) + y * Math.cos(deltaPhi) + centroid.getY();

			point.setLocation(xRes, yRes);
		}

		alpha = phi;
	}

	public int getPixel(double x, double y)
	{
		x -= centroid.getX();
		y -= centroid.getY();

		return source.getPixel(Math.round(x * Math.cos(alpha) + y * Math.sin(alpha) + initialPoint.getX()),
		                       Math.round(-x * Math.sin(alpha) + y * Math.cos(alpha) + initialPoint.getY()));
	}

	public Point2D.Double[] getVertices()
	{
		Point2D.Double[] result = new Point2D.Double[vertices.length];

		for (int i = 0; i < result.length; i++)
		{
			result[i] = new Point2D.Double(vertices[i].getX(), vertices[i].getY());
		}

		return result;
	}
}
