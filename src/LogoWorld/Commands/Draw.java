package logoworld.commands;

import logoworld.AP;

public class Draw implements Command
{
	@Override
	public void run(AP ap, String[] args)
	{
		ap.setState(true);
	}
}
