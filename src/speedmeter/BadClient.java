package speedmeter;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class BadClient 
{
	private static final int BUFFERSIZE = 16*1024 * 1024;

	public static void main(String[] args)
	{
		try (Socket socket = new Socket("10.4.0.36",7653))
		{
			OutputStream output = socket.getOutputStream();

			byte [] buffer = new byte[BUFFERSIZE];

			while(true)
			{
				output.write(buffer);
			}
		}
		catch (UnknownHostException e)
		{
			e.printStackTrace();
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
