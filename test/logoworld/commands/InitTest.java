package logoworld.commands;

import logoworld.AP;
import org.junit.Assert;
import org.junit.Test;

public class InitTest
{
	private static AP ap = new AP();

	@Test
	public void testInit()
	{
		ap.init(3, 7, 2, 1);

		Assert.assertEquals(2, ap.getX());
		Assert.assertEquals(1, ap.getY());
		Assert.assertEquals(3, ap.getWidth());
		Assert.assertEquals(7, ap.getHeight());

		ap.init(6, 3, 5, 0);

		Assert.assertEquals(5, ap.getX());
		Assert.assertEquals(0, ap.getY());
		Assert.assertEquals(6, ap.getWidth());
		Assert.assertEquals(3, ap.getHeight());
	}
}
