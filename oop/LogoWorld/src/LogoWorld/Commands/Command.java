package logoworld.commands;

import logoworld.AP;
import logoworld.BadCommandException;

public interface Command
{
	void run(AP ap, String[] args) throws BadCommandException;
}
