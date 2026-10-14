package ru.nsu.fit.djachenko.plot;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.ValueAxis;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class MainClass extends JFrame
{
	public static void main(final String[] args)
	{
		List<JPanel> panels = new ArrayList<>();

		Function function = new Function(60);

		List<JFreeChart> charts = new LinkedList<>();

		for (int i = 0; i < 10; i++)
		{
			charts.add(function.getNextGeneration());
		}

		double max = function.getMax();

		System.out.println(max);

		for (JFreeChart chart : charts)
		{
			ValueAxis axis = chart.getXYPlot().getRangeAxis();
			axis.setRange(-max, max);

			JPanel panel = new ChartPanel(chart);
			panel.setPreferredSize(new Dimension(720, 640));

			panels.add(panel);
		}

		new Window(panels).setVisible(true);
	}
}