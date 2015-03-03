package ru.nsu.fit.djachenko.knot.model;

public class MyPoint3D
{
	public double x;
	public double y;
	public double z;

	MyPoint3D()
	{
		this(0, 0, 0);
	}

	MyPoint3D(MyPoint3D other)
	{
		this(other.x, other.y, other.z);
	}

	public MyPoint3D(double x, double y, double z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}

	void setLocation(MyPoint3D other)
	{
		setLocation(other.x, other.y, other.z);
	}

	void setLocation(double x, double y, double z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public void turn(double alpha, double beta, double gamma, MyPoint3D center)
	{
		subtract(center);

		MyPoint3D temp = new MyPoint3D(this);

		temp.y = y * Math.cos(alpha) - z * Math.sin(alpha);
		temp.z = y * Math.sin(alpha) + z  * Math.cos(alpha);

		setLocation(temp);

		temp.x = x * Math.cos(beta) + z * Math.sin(beta);
		temp.z = - x * Math.sin(beta) + z * Math.cos(beta);

		setLocation(temp);

		temp.x = x * Math.cos(gamma) - y * Math.sin(gamma);
		temp.y = x * Math.sin(gamma) + y * Math.cos(gamma);

		setLocation(temp);

		add(center);
	}

	public void add(MyPoint3D other)
	{
		setLocation(x + other.x, y + other.y, z + other.z);
	}

	public void add(double x, double y, double z)
	{
		setLocation(this.x + x, this.y + y, this.z + z);
	}

	public void subtract(MyPoint3D other)
	{
		multiply(-1);
		add(other);
		multiply(-1);
	}

	public void subtract(double x, double y, double z)
	{
		multiply(-1);
		add(x, y, z);
		multiply(-1);
	}

	public void multiply(double a)
	{
		setLocation(x * a, y * a, z * a);
	}

	@Override
	public String toString()
	{
		return "(" + x + "; " + y + "; " + z + ')';
	}
}