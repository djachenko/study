package logoworld.commands;

import logoworld.AP;

public class Init implements Command
{
    @Override
	public void run(AP ap, String[] args)
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

		ap.init(intArgs[0], intArgs[1], intArgs[2], intArgs[3]);
	}
}
