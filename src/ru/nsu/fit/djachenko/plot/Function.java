package ru.nsu.fit.djachenko.plot;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

public class Function
{
	private double[] u;
	private double[] uc;

	private int size;

	private static double R = 0.5;

	private int generation = 0;

	private double max = 0;

	Function(int size)
	{
		this.size = size;

		u = new double[size];
		uc = new double[size];

		for (int i = 0; i < size / 2; i++)
		{
			u[i] = uc[i] = 1;
		}
	}

	JFreeChart getNextGeneration()
	{
		double[] temp = u;
		u = uc;
		uc = temp;

		for (int i = 0; i < size - 1; i++)
		{
			u[i] = uc[i] - R * (uc[i + 1] - uc[i]);

			double abs = Math.abs(u[i]);

			if (abs > max)
			{
				max = abs;
			}
		}

		generation++;

		XYSeries series = new XYSeries("Series" + generation);

		for (int x = 0; x < size; x++)
		{
			series.add(x, u[x]);
		}

		XYSeriesCollection collection = new XYSeriesCollection(series);

		return ChartFactory.createXYLineChart("Generation " + generation, "X", "Y", collection);
	}

	double getMax()
	{
		return max;
	}
}
