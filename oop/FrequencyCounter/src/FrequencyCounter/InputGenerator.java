package FrequencyCounter;

import java.io.IOException;
import java.lang.String;
import java.util.Random;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.io.FileOutputStream;

public class InputGenerator
{
	public static void main(String[] args)
	{
		Random generator = new Random();

		Writer writer = null;

		try
		{
			writer = new OutputStreamWriter(new FileOutputStream(args[0]));

			String alphabet = "abcdefgh";

			for (int i = 0; i < 10000; i++)
			{
				int length = Math.abs(generator.nextInt()) % 3 +1;

				for (int j = 0; j < length; j++)
				{
					writer.write(alphabet.charAt(Math.abs(generator.nextInt()) % alphabet.length()));
				}

				if (i != 9999)
				{
					writer.write(' ');
				}
			}
		}
		catch (IOException excptn)
		{
			System.err.println("Error while writing " + excptn.getLocalizedMessage());
		}
		finally
		{
			if (null != writer)
			{
				try
				{
					writer.close();
				}
				catch (IOException excptn)
				{
					excptn.printStackTrace(System.err);
				}
			}
		}
	}
}
