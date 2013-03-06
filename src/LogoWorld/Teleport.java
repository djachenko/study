package LogoWorld;

public class Teleport implements Command
{
	@Override
	public void run(Drawer AI, String[] args)
	{
        try
        {
			AI.move(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        }
        catch (NumberFormatException e)
        {
	        System.err.println("Wrong TELEPORT argument");
	        e.printStackTrace();
        }
	}
}
