package ru.nsu.fit.djachenko.graphics.function2d.view;

import ru.nsu.fit.djachenko.graphics.function2d.model.Function;

import javax.swing.*;
import java.awt.*;

public class Legend extends JPanel
{
	private static class ColorMap extends JLabel
	{
		private final Color[] colors;

		ColorMap(int width, int[] colors)
		{
			this.colors = new Color[colors.length];

			for (int i = 0; i < colors.length; i++)
			{
				this.colors[i] = new Color(colors[i]);
			}

			initUI(width);
		}

		private void initUI(int width)
		{
			setPreferredSize(new Dimension(width, getHeight()));
		}

		@Override
		protected void paintComponent(Graphics g)
		{
			super.paintComponent(g);

			int width = getWidth();
			int height = getHeight();

			double step = 1.0 * height / colors.length;

			Color previous = g.getColor();

			for (int y = 0; y < height; y++)
			{
				g.setColor(colors[(int)Math.floor(1.0 * y / step)]);

				g.drawLine(0, y, width, y);
			}

			g.setColor(previous);
		}
	}

	Legend(int[] colors)
	{
		initUI(colors);
	}

	private void initUI(int[] colors)
	{
		setLayout(new GridBagLayout());

		double min = Function.count(0, 0);
		double max = Function.count(0, 0);

		for (int y = 0; y < Canvas.DEFAULT_HEIGHT; y++)
		{
			for (int x = 0; x < Canvas.DEFAULT_WIDTH; x++)
			{
				double value = Function.count(x, y);

				min = value < min ? value : min;
				max = value > max ? value : max;
			}
		}

		int k = colors.length;

		double step = (max - min) / k;

		for (int i = 0; i <= k; i++)
		{
			GridBagConstraints labelConstraints = new GridBagConstraints();

			labelConstraints.gridx = 0;
			labelConstraints.gridy = i;
			labelConstraints.weighty = 1;
			labelConstraints.anchor = GridBagConstraints.CENTER;

			add(new JLabel(String.valueOf(Math.round((min + step * i) * 100) / 100.0)), labelConstraints);
		}

		JLabel legendColors = new ColorMap(20, colors);

		GridBagConstraints colorConstraints = new GridBagConstraints();

		colorConstraints.gridx = 1;
		colorConstraints.gridheight = k + 1;
		colorConstraints.weighty = 1;
		colorConstraints.fill = GridBagConstraints.VERTICAL;
		colorConstraints.insets = new Insets(10, 5, 10, 5);

		add(legendColors, colorConstraints);
		legendColors.repaint();
	}
}
