package LogoWorld.Commands;

import LogoWorld.Drawer;

public class Draw implements Command
{
	@Override
	public void run(Drawer AI, String[] args)
	{
		AI.setState(true);
	}
}
