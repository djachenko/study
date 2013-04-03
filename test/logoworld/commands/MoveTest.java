package logoworld.commands;

import logoworld.AP;
import logoworld.BadCommandException;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class MoveTest
{
	private static AP ap = null;

	@Before
	public void prepare()
	{
		ap = new AP();

		ap.init(3, 3, 0, 0);
	}

	@Test
	public void testMove()
	{
		try
		{
			new Draw().run(ap, new String[]{});

			new Move().run(ap, new String[]{"R", "2"});

			for (int i = 0; i < 2; i++)
			{
				Assert.assertEquals(true, ap.getCell(1 + i, 0));
			}

			new Ward().run(ap, new String[]{});
			new Move().run(ap, new String[]{"D", "2"});

			for (int i = 0; i < 2; i++)
			{
				Assert.assertEquals(false, ap.getCell(2, 1 + i));
			}

			new Draw().run(ap, new String[]{});
			new Move().run(ap, new String[]{"L", "2"});

			for (int i = 0; i < 2; i++)
			{
				Assert.assertEquals(true, ap.getCell(1 - i, 2));
			}

			new Move().run(ap, new String[]{"U", "1"});

			Assert.assertEquals(true, ap.getCell(0, 1));
			Assert.assertEquals(false, ap.getCell(0, 0));
		}
		catch (BadCommandException e)
		{
			e.printStackTrace();
		}
	}

}
