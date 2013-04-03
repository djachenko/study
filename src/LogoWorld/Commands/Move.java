package logoworld.commands;

import logoworld.AP;

public class Move implements Command
{
	enum Direction{L, R, U, D}

	@Override
	public void run(AP ap, String[] args)
	{
		Direction dir = Direction.valueOf(args[0]);

		for (int i = 0; i < Integer.parseInt(args[1]); i++)
		{
			switch (dir)
			{
				case L:
					ap.move(ap.getX() - 1, ap.getY());
					break;
				case R:
					ap.move(ap.getX() + 1, ap.getY());
					break;
				case U:
					ap.move(ap.getX(), ap.getY() - 1);
					break;
				case D:
					ap.move(ap.getX(), ap.getY() + 1);
					break;
				default:
					System.out.println("WTF?");
			}

			ap.setCell();
		}
	}
}
