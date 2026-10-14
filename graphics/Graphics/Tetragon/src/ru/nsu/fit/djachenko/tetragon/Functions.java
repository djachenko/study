package ru.nsu.fit.djachenko.tetragon;

import java.awt.geom.Point2D;

public class Functions
{
	public static boolean intersect(Point2D a, Point2D b, Point2D c, Point2D d)
	{
		return intersectRay(a, b, c, d) && intersectRay(c, d, a, b);
	}

	public static boolean intersectRay(Point2D a, Point2D b, Point2D c, Point2D d)
	{
		b = new Point2D.Double(b.getX() - a.getX(), b.getY() - a.getY());
		c = new Point2D.Double(c.getX() - a.getX(), c.getY() - a.getY());
		d = new Point2D.Double(d.getX() - a.getX(), d.getY() - a.getY());
		a = new Point2D.Double();

		double s1 = b.getX() * c.getY() - c.getX() * b.getY();
		double s2 = b.getX() * d.getY() - d.getX() * b.getY();

		final double epsilon = 0.0000001;

		if (Math.abs(s1) < epsilon && Math.abs(s2) < epsilon)
		{
			if (Math.abs(b.getX()) < epsilon)
			{
				return Math.min(a.getY(), b.getY()) <= Math.max(c.getY(), d.getY()) &&
				       Math.min(c.getY(), d.getY()) <= Math.max(a.getY(), b.getY());
			}
			else
			{
				return Math.min(a.getX(), b.getX()) <= Math.max(c.getX(), d.getX()) &&
				       Math.min(c.getX(), d.getX()) <= Math.max(a.getX(), b.getX());
			}
		}
		else
		{
			return s1 * s2 <= 0;
		}
	}
}