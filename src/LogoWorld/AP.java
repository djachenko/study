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
		field = new boolean[height][];

		for (int i = 0; i < x; i++)
		{
			field[i] = new boolean[width];
		}

		this.x = x;
		this.y = y;
		state = false;
	}

	public void setState(boolean state)
	{
		this.state = state;
	}

	public void setCell()
	{
		field[x][y] = this.state;
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

	public void draw()
	{
		for (boolean[] line : field)
		{
			for (boolean cell : line)
			{
				if (cell)
				{
					System.out.print(' ');
				} else
				{
					System.out.print('X');
				}
			}

			System.out.println();
		}
	}
}
