package logoworld.commands;

import logoworld.AP;
import logoworld.BadCommandException;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class WardTest
{
	static AP ap = null;

	@Before
	public void prepare()
	{
		ap = new AP();

		ap.init(1, 1, 0, 0);
	}

	@Test
	public void testWard()
	{
		try
		{
			new Draw().run(ap, new String[1]);
		}
		catch (BadCommandException e)
		{
			e.printStackTrace();
		}

		ap.setCell();

		Assert.assertEquals(ap.getCell(0, 0), true);

		try
		{
			new Ward().run(ap, new String[1]);
		}
		catch (BadCommandException e)
		{
			e.printStackTrace();
		}

		ap.setCell();

		Assert.assertEquals(ap.getCell(0, 0), false);
	}
}
