package porttranslator;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Translator
{
	public static void main(String[] args)
	{
		Properties portList = new Properties();

		try
		{
			portList.load(new FileReader(args[0]));


		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
