package LogoWorld;

public class Drawer
{
	private boolean [][] field;
	private int x;
	private int y;

	Drawer(int width, int height, int x, int y)
	{
		field = new boolean[height][];

		for(int i = 0; i < x; i++)
		{
			field[i] = new boolean[width];
		}

		this.x = x;
		this.y = y;
	}

	public void set()
	{
		field[x][y] = true;
	}

	public void unset()
	{
		field[x][y] = false;
	}


	public void move(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	public void draw()
	{
		for (int i = 0; i < field.length; i++)
		{
			for (int j = 0; j < field[i].length; j++)
			{
				if (field[i][j])
				{
					System.out.print(' ');
				}
				else
				{
					System.out.print('X');
				}
			}

			System.out.println();
		}
	}
}
