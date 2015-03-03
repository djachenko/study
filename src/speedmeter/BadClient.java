package speedmeter;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

public class BadClient 
{
	private static final int BUFFERSIZE = 1024 * 1024;

	public static void main(String[] args)
	{
		try (Socket socket = new Socket("192.168.1.7",7653))
		{
			OutputStream output = socket.getOutputStream();

			byte [] buffer = new byte[BUFFERSIZE];

			while(true)
			{
				output.write(buffer);
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		catch (Exception e)
		{
			System.err.println(e.getLocalizedMessage());

			e.printStackTrace();
		}
	
	}
}
