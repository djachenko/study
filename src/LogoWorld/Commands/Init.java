package LogoWorld.Commands;

import LogoWorld.Drawer;

public class Init implements Command
{
    @Override
	public void run(Drawer AI, String[] args)
	{
		Integer[] intArgs = new Integer[args.length];

		for (int i = 0; i < intArgs.length; i++)
		{
			try
			{
				intArgs[i] = Integer.parseInt(args[i]);//можно ли параллельный foreach?
			}
			catch (NumberFormatException e)
			{
				System.err.println("Wrong parameter #" + i + "in Init");
				e.printStackTrace();
			}
		}

		AI.init(intArgs[0], intArgs[1], intArgs[2], intArgs[3]);
	}
}
