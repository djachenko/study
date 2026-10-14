package ru.nsu.fit.djachenko.tetragon.view;

import ru.nsu.fit.djachenko.tetragon.model.Tetragon;

import java.awt.geom.Point2D;
import java.util.Random;

public class TetragonGenerator
{
	private final Random random = new Random(System.currentTimeMillis());

	Tetragon generate()
	{
		Tetragon result = new Tetragon(new Point2D.Double(random.nextDouble(), random.nextDouble()),
		                               new Point2D.Double(random.nextDouble(), random.nextDouble()),
		                               new Point2D.Double(random.nextDouble(), random.nextDouble()),
		                               new Point2D.Double(random.nextDouble(), random.nextDouble()));

		while (result.isComplex())
		{
			result = new Tetragon(new Point2D.Double(random.nextDouble(), random.nextDouble()),
			                      new Point2D.Double(random.nextDouble(), random.nextDouble()),
			                      new Point2D.Double(random.nextDouble(), random.nextDouble()),
			                      new Point2D.Double(random.nextDouble(), random.nextDouble()));
		}

		return result;
	}
}
