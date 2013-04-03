package logoworld.commands;

import logoworld.AP;

public class Teleport implements Command
{
	@Override
	public void run(AP ap, String[] args)
	{
        try
        {
			ap.move(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        }
        catch (NumberFormatException e)
        {
	        System.err.println("Wrong TELEPORT argument");
	        e.printStackTrace();
        }
	}
}
