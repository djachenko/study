package LogoWorld;

public class Draw implements Command
{
	@Override
	public void run(Drawer AI, String[] args)
	{
		AI.setState(true);
	}
}
