package ru.nsu.fit.djachenko.knot.model;

public abstract class Knot
{
	private final MyPoint3D shift = new MyPoint3D();

	private double alpha = 0;
	private double beta = 0;
	private double gamma = 0;

	public abstract MyPoint3D count(double t);

	public double from()
	{
		return 0;
	}

	public double to()
	{
		return 2 * Math.PI;
	}

	public synchronized void turn(double alpha, double beta, double gamma)
	{
		gamma *= -1;

		this.alpha += alpha;
		this.beta += beta;
		this.gamma += gamma;
	}

	public void move(double dx, double dy, double dz)
	{
		shift.add(dx, dy, dz);
	}

	public MyPoint3D getShift()
	{
		return shift;
	}

	public double getAlpha()
	{
		return alpha;
	}

	public double getBeta()
	{
		return beta;
	}

	public double getGamma()
	{
		return gamma;
	}

	public abstract Cube getBounds();
}
