package ru.nsu.fit.djachenko.graphics.function2d.view;

import ru.nsu.fit.djachenko.graphics.function2d.model.Function;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

public class Canvas extends JPanel
{
	public static final int DEFAULT_HEIGHT = 256;
	public static final int DEFAULT_WIDTH = 256;

	private int gridWidth = 64;
	private int gridHeight = 64;

	private double gridWidthMultiplier = 1.0 * DEFAULT_WIDTH / gridWidth;
	private double gridHeightMultiplier = 1.0 * DEFAULT_HEIGHT / gridHeight;

	private static final Color GRID_COLOR = Color.CYAN;

	private double min;
	private final double step;

	private final int[] legend;

	public static enum Mode
	{
		AREAS,
		INTERPOLATION,
		DITHERING
	}

	private Mode mode = Mode.AREAS;
	private boolean isolinesEnabled = false;
	private boolean gridEnabled = false;

	public Canvas(int[] colors, InfoPanel infoPanel)
	{
		this.legend = colors;

		min = Function.count(0, 0);
		double max = Function.count(0, 0);

		for (int y = 0; y <= DEFAULT_HEIGHT; y++)
		{
			for (int x = 0; x <= DEFAULT_WIDTH; x++)
			{
				double value = Function.count(x, y);

				min = value < min ? value : min;
				max = value > max ? value : max;
			}
		}

		step = (max - min) / legend.length;

		initUI(infoPanel);
	}

	private void initUI(InfoPanel infoPanel)
	{
		setLayout(new BoxLayout(this, BoxLayout.X_AXIS));

		setPreferredSize(new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT));

		addMouseMotionListener(new MouseMotionAdapter()
		{
			@Override
			public void mouseMoved(MouseEvent e)
			{
				double widthMultiplier = 1.0 * DEFAULT_WIDTH / getWidth();
				double heightMultiplier = 1.0 * DEFAULT_HEIGHT / getHeight();

				infoPanel.set(e.getX(), e.getY(), Function.count(widthMultiplier * e.getX(), heightMultiplier * e.getY()));

				repaint();
			}
		});
	}

	@Override
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);

		switch (mode)
		{
			case AREAS:
			case INTERPOLATION:
				drawFunction(g);
				break;
			case DITHERING:
				drawSteinberg(g);
				break;
			default:
				break;
		}

		if (isolinesEnabled)
		{
			drawIsolines(g);
		}

		if (gridEnabled)
		{
			drawGrid(g);
		}
	}

	private void setPixel(Graphics g, int x, int y, int rgb)
	{
		setPixel(g, x, y, new Color(rgb));
	}

	private void setPixel(Graphics g, int x, int y, Color color)
	{
		Color previous = g.getColor();

		g.setColor(color);

		g.drawLine(x, y, x, y);

		g.setColor(previous);
	}

	private void drawIsolines(Graphics g)
	{
		double[] func = new double[4];
		boolean[] intersections = new boolean[4];
		int intersectionsCount;

		int[] intersectionXs = new int[4];
		int[] intersectionYs = new int[4];

		double xStep = 1.0 * getWidth() / gridWidth;
		double yStep = 1.0 * getHeight() / gridHeight;

		Color color = g.getColor();

		g.setColor(GRID_COLOR);

		for (int k = 0; k < legend.length; k++)
		{
			double isoline = min + k * step;

			for (int y = 0; y < gridHeight; y++)
			{
				for (int x = 0; x < gridWidth; x++)
				{
					func[0] = Function.count(gridWidthMultiplier * x,         gridHeightMultiplier * y);
					func[1] = Function.count(gridWidthMultiplier * (x + 1),   gridHeightMultiplier * y);
					func[2] = Function.count(gridWidthMultiplier * (x + 1),   gridHeightMultiplier * (y + 1));
					func[3] = Function.count(gridWidthMultiplier * x,         gridHeightMultiplier * (y + 1));

					intersectionsCount = 0;

					for (int i = 0; i < intersections.length; i++)
					{
						intersections[i] = (func[i] - isoline) * (func[(i + 1) % func.length] - isoline) <= 0;//&& (isoline - func[i]) > 0.00001;

						if (intersections[i])
						{
							switch (i)
							{
								case 0://top
									intersectionXs[i] = (int)Math.round(xStep * (x + (isoline - func[0]) / (func[1] - func[0])));
									intersectionYs[i] = (int)Math.round(yStep * y);
									break;
								case 1://right
									intersectionXs[i] = (int)Math.round(xStep * (x + 1));
									intersectionYs[i] = (int)Math.round(yStep * (y + (isoline - func[1]) / (func[2] - func[1])));
									break;
								case 2://bottom
									intersectionXs[i] = (int)Math.round(xStep * (x + (isoline - func[3]) / (func[2] - func[3])));
									intersectionYs[i] = (int)Math.round(yStep * (y + 1));
									break;
								case 3://left
									intersectionXs[i] = (int)Math.round(xStep * x);
									intersectionYs[i] = (int)Math.round(yStep * (y + (isoline - func[0]) / (func[3] - func[0])));
									break;
							}

							intersectionsCount++;
						}
					}

					if (intersectionsCount == 2)
					{
						int x1 = 0;
						int y1 = 0;

						for (int i = 0; i < 4; i++)
						{
							if (intersections[i])
							{
								x1 = intersectionXs[i];
								y1 = intersectionYs[i];

								break;
							}
						}

						int x2 = 0;
						int y2 = 0;

						for (int i = 3; i >= 0; i--)
						{
							if (intersections[i])
							{
								x2 = intersectionXs[i];
								y2 = intersectionYs[i];

								break;
							}
						}

						g.drawLine(x1, y1, x2, y2);
					}
				}
			}
		}

		g.setColor(color);
	}

	private void drawFunction(Graphics g)
	{
		int width = getWidth();
		int height = getHeight();

		double widthMultiplier = 1.0 * DEFAULT_WIDTH / width;
		double heightMultiplier = 1.0 * DEFAULT_HEIGHT / height;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int index = (int)Math.floor((Function.count(widthMultiplier * x, heightMultiplier * y) - min) / step);

				if (index >= 0 && index < legend.length)
				{
					switch (mode)
					{
						case AREAS:
							setPixel(g, x, y, legend[index]);
							break;
						case INTERPOLATION:
							setPixel(g, x, y, interpolatedColor(x, y));
							break;
						default:
							break;
					}
				}
			}
		}
	}

	private void drawGrid(Graphics g)
	{
		Color color = g.getColor();

		g.setColor(GRID_COLOR);

		int width = getWidth();
		int height = getHeight();

		double gridStepX = 1.0 * width / gridWidth;
		double gridStepY = 1.0 * height / gridHeight;

		for (int i = 1; i < gridWidth; i++)
		{
			int x = (int)Math.round(i * gridStepX);

			g.drawLine(x, 0, x, height - 1);
		}

		for (int i = 1; i < gridHeight; i++)
		{
			int y = (int)Math.round(i * gridStepY);

			g.drawLine(0, y, width - 1, y);
		}

		g.setColor(color);
	}

	private int interpolatedColor(int x, int y)
	{
		double widthMultiplier = 1.0 * DEFAULT_WIDTH / getWidth();
		double heightMultiplier = 1.0 * DEFAULT_HEIGHT / getHeight();

		double value = Function.count(widthMultiplier * x, heightMultiplier * y) - min;

		double part = value / step;

		int index = (int)Math.floor(part);

		if (index == 0 || index == legend.length - 1)
		{
			return legend[index];
		}
		else
		{
			double lower;
			double current;
			double upper;

			if (part - index < 0.5)
			{
				lower = index + 0.5 - part;
				current = 1 - lower;
				upper = 0;
			}
			else
			{
				lower = 0;
				current = index + 1.5 - part;
				upper = 1 - current;
			}

			int result = 0;

			for (int i = 0; i < 4; i++)
			{
				result |= (int)Math.round(((legend[index - 1] >> i * 8) & 0xFF) * lower +
				                          ((legend[index] >> i * 8) & 0xFF) * current +
				                          ((legend[index + 1] >> i * 8) & 0xFF) * upper) << i * 8;
			}

			return result;
		}
	}

	private void drawSteinberg(Graphics g)
	{
		int height = getHeight();
		int width = getWidth();

		double widthMultiplier = 1.0 * DEFAULT_WIDTH / width;
		double heightMultiplier = 1.0 * DEFAULT_HEIGHT / height;

		int[] currentLineError;
		int[] nextLineError = new int[width];

		for (int y = 0; y < height; y++)
		{
			currentLineError = nextLineError;
			nextLineError = new int[width];

			for (int x = 0; x < width; x++)
			{
				int index = (int)Math.floor((Function.count(widthMultiplier * x, heightMultiplier * y) - min) / step);

				if (!(index >= 0 && index < legend.length))
				{
					break;
				}

				int interpolated = addColors(interpolatedColor(x, y), currentLineError[x]);

				int closest = findClosestPaletteColor(interpolated);

				setPixel(g, x, y, closest);

				int error = subColors(interpolated, closest);

				if (x != width - 1)
				{
					currentLineError[x + 1] += mulColor(error, 7.0 / 16);
					nextLineError[x + 1] += mulColor(error, 1.0 / 16);
				}

				if (x != 0)
				{
					nextLineError[x - 1] += mulColor(error, 3.0 / 16);
				}

				nextLineError[x] += mulColor(error, 5.0 / 16);
			}
		}
	}

	private int findClosestPaletteColor(int source)
	{
		int closest = legend[0];
		int difference = diff(closest, source);

		for (int color : legend)
		{
			if (diff(source, color) < difference)
			{
				closest = color;
				difference = diff(closest, source);
			}
		}

		return closest;
	}

	private int diff(int a, int b)
	{
		int result = 0;

		for (int i = 0; i < 4; i++)
		{
			int difference = (a >> i * 8) & 0xFF - (b >> i * 8) & 0xFF;

			result += (difference * difference) << (i * 8);
		}

		return result;
	}

	private static int addColors(int a, int b)
	{
		int result = 0;

		for (int i = 0; i < 4; i++)
		{
			result |= Math.max(0, Math.min(255, (((a >> i * 8) + (b >> i * 8)) & 0xFF))) << i * 8;
		}

		return result;
	}

	private static int subColors(int a, int b)
	{
		int result = 0;

		for (int i = 0; i < 4; i++)
		{
			result |= Math.max(0, Math.min(255, (((a >> i * 8) - (b >> i * 8)) & 0xFF))) << i * 8;
		}

		return result;
	}

	private static int mulColor(int rgb, double m)
	{
		int result = 0;

		for (int i = 0; i < 4; i++)
		{
			result |= (int)Math.max(0, Math.min(255, ((rgb >> (i * 8) & 0xFF) * m))) << i * 8;
		}

		return result;
	}

	public void setMode(Mode mode)
	{
		this.mode = mode;

		repaint();
	}

	public void setIsolinesEnabled(boolean isolinesEnabled)
	{
		this.isolinesEnabled = isolinesEnabled;
		repaint();
	}

	public boolean isIsolinesEnabled()
	{
		return isolinesEnabled;
	}

	public void setGridEnabled(boolean gridEnabled)
	{
		this.gridEnabled = gridEnabled;
		repaint();
	}
}
