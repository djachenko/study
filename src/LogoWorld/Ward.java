package LogoWorld;

public class Ward implements Command
{
	@Override
	public void run(Drawer AI, String[] args)
	{
		AI.setState(false);
	}
}
