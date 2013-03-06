package LogoWorld;

public class Move implements Command
{
	enum Direction{L, R, U, D}

	@Override
	public void run(Drawer AI, String[] args)
	{
		Direction dir = Direction.valueOf(args[0]);

		for (int i = 0; i < Integer.parseInt(args[1]); i++)
		{
			switch (dir)
			{
				case L:
					AI.move(AI.getX() - 1, AI.getY());
					break;
				case R:
					AI.move(AI.getX() + 1, AI.getY());
					break;
				case U:
					AI.move(AI.getX(), AI.getY() + 1);
					break;
				case D:
					AI.move(AI.getX(), AI.getY() - 1);
					break;
				default:
					System.out.println("WTF?");
			}

			AI.setCell();
		}
	}
}
