package ru.nsu.fit.djachenko.tetragon.model;

import java.awt.geom.Point2D;
import java.util.List;
import java.util.function.Function;

public class TriangleMapper implements Function<Point2D.Double, Point2D.Double>
{
	private final double a;
	private final double b;
	private final double c;
	private final double d;
	private final double e;
	private final double f;

	public TriangleMapper(Triangle from)
	{
		List<Point2D.Double> fromPoints = from.getPoints();
		List<Point2D.Double> toPoints = from.getMappings();

		double[][] A = new double[6][6];
		double[] B = new double[6];

		for (int y = 0; y < 3; y++)
		{
			A[y][0] = fromPoints.get(y).getX();
			A[y][1] = fromPoints.get(y).getY();
			A[y][2] = 1;
		}

		for (int y = 3; y < 6; y++)
		{
			A[y][3] = fromPoints.get(y - 3).getX();
			A[y][4] = fromPoints.get(y - 3).getY();
			A[y][5] = 1;
		}

		for (int i = 0; i < toPoints.size(); i++)
		{
			B[i] = toPoints.get(i).getX();
		}

		for (int i = 0; i < toPoints.size(); i++)
		{
			B[i + 3] = toPoints.get(i).getY();
		}

		double[] coefficients = GaussianEquation.solve(A, B);

		a = coefficients[0];
		b = coefficients[1];
		c = coefficients[2];
		d = coefficients[3];
		e = coefficients[4];
		f = coefficients[5];
	}

	@Override
	public Point2D.Double apply(Point2D.Double point)
	{
		double x = point.x;
		double y = point.y;

		double u = (a * x + b * y + c);
		double v = (d * x + e * y + f);

		return new Point2D.Double(u, v);
	}
}
