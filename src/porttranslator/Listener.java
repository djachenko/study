package porttranslator;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Listener extends Thread
{
	private ServerSocket socket = null;
	private InetAddress address = null;
	private int port = 0;

	Listener(int localPort, InetAddress address, int port)
	{
		try
		{
			socket = new ServerSocket(localPort);

			System.out.println("Listener port is " + socket.getLocalPort());

			this.address = address;
			this.port = port;
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	@Override
	public void run()
	{
		try(Socket incoming = socket.accept();)
		{
			try (Socket outcoming = new Socket(address, port))
			{
				new Writer(incoming.getInputStream(), outcoming.getOutputStream()).start();
				new Writer(outcoming.getInputStream(), incoming.getOutputStream()).start();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		finally
		{
        	try
			{
				socket.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
	}
}
