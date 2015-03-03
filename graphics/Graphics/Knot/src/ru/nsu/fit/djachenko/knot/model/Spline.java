package ru.nsu.fit.djachenko.knot.model;

public class Spline
{
	private final MyPoint3D[] points;

	public Spline(MyPoint3D[] points)
	{
		this.points = points;
	}

	public MyPoint3D count(double t)
	{
		int size = points.length;
		MyPoint3D value = new MyPoint3D();

		for (int i = 0; i < size; i++)
		{
			MyPoint3D temp = new MyPoint3D(points[i]);
			temp.multiply(coefficient(size - 1, i) * Math.pow(t, i) * Math.pow(1 - t, size - 1 - i));
			value.add(temp);
		}

		return value;
	}

	private int coefficient(final int n, final int k)
	{
		if (0 == k || n == k)
		{
			return 1;
		}
		else
		{
			return coefficient(n - 1, k - 1) + coefficient(n - 1, k);
		}
	}
}
