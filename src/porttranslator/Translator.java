package porttranslator;

import java.io.FileReader;
import java.io.IOException;
import java.net.InetAddress;
import java.util.Properties;

public class Translator
{
	public static void main(String[] args)
	{
		Properties portList = new Properties();

		try(FileReader reader = new FileReader(args[0]))
		{
			portList.load(reader);

			for (String localPort : portList.stringPropertyNames())
			{
				String [] listenerArgs = portList.getProperty(localPort).replaceAll("\\s+", " ").trim().split(" ");

				new Listener(Integer.parseInt(localPort), InetAddress.getByName(listenerArgs[0]), Integer.parseInt(listenerArgs[1])).start();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
