package ru.nsu.fit.djachenko.tetragon.model;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

public class TetragonMapper implements Function<Point2D.Double, Point2D.Double>
{
	private final double a;
	private final double b;
	private final double c;
	private final double d;
	private final double e;
	private final double f;
	private final double g;
	private final double h;

	public TetragonMapper(Tetragon from)
	{
		List<Point2D.Double> fromPoints = from.getPoints();
		List<Point2D.Double> toPoints = new ArrayList<>();

		toPoints.add(new Point2D.Double(0, 0));
		toPoints.add(new Point2D.Double(1, 0));
		toPoints.add(new Point2D.Double(1, 1));
		toPoints.add(new Point2D.Double(0, 1));

		double[][] A = new double[8][8];
		double[] B = new double[8];

		for (int i = 0; i < fromPoints.size(); i++)
		{
			Point2D.Double fromPoint = fromPoints.get(i);
			Point2D.Double toPoint = toPoints.get(i);

			A[2 * i][0] = fromPoint.x;
			A[2 * i][1] = fromPoint.y;
			A[2 * i][2] = 1;
			A[2 * i][6] = -1 * toPoint.x * fromPoint.x;
			A[2 * i][7] = -1 * toPoint.x * fromPoint.y;

			A[2 * i + 1][3] = fromPoint.x;
			A[2 * i + 1][4] = fromPoint.y;
			A[2 * i + 1][5] = 1;
			A[2 * i + 1][6] = -1 * toPoint.y * fromPoint.x;
			A[2 * i + 1][7] = -1 * toPoint.y * fromPoint.y;

			B[2 * i] = toPoint.x;
			B[2 * i + 1] = toPoint.y;
		}

		double[] coefficients = GaussianEquation.solve(A, B);

		a = coefficients[0];
		b = coefficients[1];
		c = coefficients[2];
		d = coefficients[3];
		e = coefficients[4];
		f = coefficients[5];
		g = coefficients[6];
		h = coefficients[7];
	}

	@Override
	public Point2D.Double apply(Point2D.Double point)
	{
		double x = point.x;
		double y = point.y;

		double u = (a * x + b * y + c) / (g * x + h * y + 1);
		double v = (d * x + e * y + f) / (g * x + h * y + 1);

		return new Point2D.Double(u, v);
	}
}
