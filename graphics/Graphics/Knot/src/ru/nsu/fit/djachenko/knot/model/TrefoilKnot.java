package ru.nsu.fit.djachenko.knot.model;

public class TrefoilKnot extends Knot
{
	private final MyPoint3D center = new MyPoint3D();
	private final Cube bound;

	public static final int TEST_POINTS_COUNT = 256;

	public TrefoilKnot()
	{
		double step = (to() - from()) / TEST_POINTS_COUNT;

		MyPoint3D[] bounds = new MyPoint3D[2];
		bounds[0] = count(0);
		bounds[1] = count(0);

		for (int i = 0; i < TEST_POINTS_COUNT; i++)
		{
			MyPoint3D point = count(step * i);

			bounds[0].setLocation(Math.min(bounds[0].x, point.x),
			                      Math.min(bounds[0].y, point.y),
			                      Math.min(bounds[0].z, point.z));

			bounds[1].setLocation(Math.max(bounds[1].x, point.x),
			                      Math.max(bounds[1].y, point.y),
			                      Math.max(bounds[1].z, point.z));
		}

		center.setLocation((bounds[0].x + bounds[1].x) / 2,
		                   (bounds[0].y + bounds[1].y) / 2,
		                   (bounds[0].z + bounds[1].z) / 2);

		bound = new Cube(bounds[0], bounds[1]);
	}

	@Override
	public MyPoint3D count(double t)
	{
		double x = Math.sin(t) + 2 * Math.sin(2 * t);
		double y = Math.cos(t) - 2 * Math.cos(2 * t);
		double z = - Math.sin(3 * t);

		MyPoint3D result = new MyPoint3D(x, y, z);

		result.multiply(50);

		result.turn(getAlpha(), getBeta(), getGamma(), center);
		result.add(getShift());

		return result;
	}

	@Override
	public synchronized void turn(double alpha, double beta, double gamma)
	{
		super.turn(alpha, beta, gamma);

		bound.turn(alpha, beta, gamma);
	}

	@Override
	public void move(double dx, double dy, double dz)
	{
		super.move(dx, dy, dz);

		bound.move(dx, dy, dz);
	}

	@Override
	public Cube getBounds()
	{
		return bound;
	}
}
