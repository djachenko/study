package ru.nsu.fit.djachenko.tetragon.model;

import java.awt.geom.Point2D;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class MIP
{
	private final List<BufferedImage> levels = new ArrayList<>();

	private boolean filterEnabled = false;

	public MIP(BufferedImage source)
	{
		levels.add(source);

		BufferedImage current = source;

		while (Math.min(current.getHeight(), current.getWidth()) > 1)
		{
			current = generateNextLevel(current);
			levels.add(current);
		}

		Collections.reverse(levels);
	}

	private BufferedImage generateNextLevel(BufferedImage currentLevel)
	{
		int height = currentLevel.getHeight();
		int width = currentLevel.getWidth();

		BufferedImage next = new BufferedImage(width / 2, height / 2, BufferedImage.TYPE_INT_RGB);

		int nextWidth = next.getWidth();
		int nextHeight = next.getHeight();

		for (int y = 0; y < nextHeight; y++)
		{
			for (int x = 0; x < nextWidth; x++)
			{
				int r = 0;
				int g = 0;
				int b = 0;

				int count = 0;

				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (2 * x + i < width &&
							2 * y + j < height)
						{
							int rgb = currentLevel.getRGB(2 * x + i, 2 * y + j);

							r += (rgb >> (2 * 8)) & 0xFF;
							g += (rgb >> 8) & 0xFF;
							b += rgb & 0xFF;

							count++;
						}
					}
				}

				r /= count;
				g /= count;
			    b /= count;

				next.setRGB(x, y, (r << (2 * 8)) | (g << 8) | b);
			}
		}

		return next;
	}

	public int getTrilineRGB(Point2D point, double delta)
	{
		int index = 9;

		while (levels.get(index).getWidth() * delta > 1)
		{
			index--;
		}

		int upper = index;
		int lower;

		if (levels.get(index).getWidth() * delta == 1 || upper == 0)
		{
			lower = upper;
		}
		else
		{
			lower = upper - 1;
		}

		BufferedImage upperTexture = levels.get(upper);
		BufferedImage lowerTexture = levels.get(lower);

		int upperColor = getBilineRGB(point, upperTexture);
		int lowerColor = getBilineRGB(point, lowerTexture);

		double upperTexelWidth = 1.0 / upperTexture.getWidth();
		double lowerTexelWidth = 1.0 / lowerTexture.getWidth();

		double lowerRatio = Math.abs((upperTexelWidth - delta) / (lowerTexelWidth - upperTexelWidth));
		double upperRatio = 1 - lowerRatio;


		return ((int) Math.round((upperColor >> 16 & 0xFF) * upperRatio + (lowerColor >> 16 & 0xFF) * lowerRatio) & 0xFF) << 16 |
		       ((int) Math.round((upperColor >> 8 & 0xFF) * upperRatio + (lowerColor >> 8 & 0xFF) * lowerRatio) & 0xFF) << 8 |
		       ((int) Math.round((upperColor & 0xFF) * upperRatio + (lowerColor & 0xFF) * lowerRatio) & 0xFF) |
		       0xFF000000;
	}

	public int getRGB(Point2D point, double delta)
	{
		return filterEnabled ? getTrilineRGB(point, delta) : getBilineRGB(point, delta);
	}

	private int getBilineRGB(Point2D point, double delta)
	{
		int index = 9;

		while (levels.get(index).getWidth() * delta > 1)
		{
			index--;
		}

		BufferedImage level = levels.get(index);

		return getBilineRGB(point, level);
	}

	private int getBilineRGB(Point2D point, BufferedImage level)
	{
		double x = point.getX() * level.getWidth();
		double y = point.getY() * level.getHeight();

		double xShift = x - Math.floor(x);
		double yShift = y - Math.floor(y);

		int textureX = (int) Math.floor(x);
		int textureY = (int) Math.floor(y);

		if (textureX >= level.getWidth())
		{
			textureX = level.getWidth() - 1;
		}

		if (textureY >= level.getHeight())
		{
			textureY = level.getHeight() - 1;
		}

		if (textureX <= 0)
		{
			textureX = 0;
		}

		if (textureY <= 0)
		{
			textureY = 0;
		}

		int textureXRight = (textureX < level.getWidth() - 1) ? textureX + 1 : textureX;
		int textureYDown = (textureY < level.getHeight() - 1) ? textureY + 1 : textureY;

		int[] neighbours = {level.getRGB(textureX, textureY),
		                    level.getRGB(textureXRight, textureY),
		                    level.getRGB(textureX, textureYDown),
		                    level.getRGB(textureXRight, textureYDown)};

		int result = 0;

		for (int i = 0; i < 4; i++)
		{
			double tmp = ((neighbours[0] >> i * 8) & 0xFF) * (1 - xShift) * (1 - yShift) +
			             ((neighbours[1] >> i * 8) & 0xFF) * xShift * (1 - yShift) +
			             ((neighbours[2] >> i * 8) & 0xFF) * (1 - xShift) * yShift +
			             ((neighbours[3] >> i * 8) & 0xFF) * xShift * yShift;

			result |= ((int) tmp << i * 8);
		}

		return result;
	}

	public void setFilterEnabled(boolean state)
	{
		filterEnabled = state;
	}
}
