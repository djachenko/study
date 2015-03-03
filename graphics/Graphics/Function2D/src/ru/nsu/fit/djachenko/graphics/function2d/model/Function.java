package ru.nsu.fit.djachenko.graphics.function2d.model;

public class Function
{
	public static double count(double x, double y)
	{
		//return x + y;
		//return Math.sqrt(x * x + y * y);
		double k = 1.0 / 16;
		return (Math.sin(k * x) + Math.cos(k * y));/**/
	}
}
