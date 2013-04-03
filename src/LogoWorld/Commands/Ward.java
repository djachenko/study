package logoworld.commands;

import logoworld.AP;

public class Ward implements Command
{
	@Override
	public void run(AP ap, String[] args)
	{
		ap.setState(false);
	}
}
