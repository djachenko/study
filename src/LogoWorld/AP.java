package LogoWorld;

public class AP
{
	private boolean[][] field;
	private int x;
	private int y;
	private boolean state;

	AP()
	{
	}

	public void init(int width, int height, int x, int y)
	{
		field = new boolean[height][width];

		for (boolean[] line : field)
		{
			for (int i = 0; i < line.length; i++)
			{
				line[i] = false;
			}
		}

		this.x = x;
		this.y = y;
		state = false;

		System.out.println("inited with " + field.length + ' ' + field[0].length);
	}

	public void setState(boolean state)
	{
		this.state = state;
	}

	public void setCell()
	{
		field[y][x] = this.state;
	}

	public void move(int x, int y)
	{
		this.x = (x + field[0].length) % field[0].length;
		this.y = (y + field.length) % field.length;
	}

	public int getX()
	{
		return x;
	}

	public int getY()
	{
		return y;
	}

	public boolean getCell(int x, int y)
	{
		return field[x][y];
	}

	public int getWidth()
	{
		return field[0].length;
	}

	public int getHeight()
	{
		return field.length;
	}
}
