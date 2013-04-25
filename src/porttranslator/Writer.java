package porttranslator;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class Writer extends Thread
{
	InputStream from = null;
	OutputStream to = null;

	public Writer(InputStream in, OutputStream out)
	{
		from =  in;
		to = out;
	}

	@Override
	public void run()
	{
		byte [] buffer = new byte[1024];

		try
		{
			while (true)
			{
                int read = from.read(buffer);

				if (read == -1)
				{
					break;
				}

				to.write(buffer, 0, read);
			}

			from.close();
			to.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
