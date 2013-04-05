package filetransmitter;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Receiver
{
	public static void main(String[] args)
	{
		try
		{
			ServerSocket socket = new ServerSocket(7686);

			Socket incoming = socket.accept();

			incoming.getInputStream().read(new byte[1024]);

			System.out.println("got");

			System.out.println("other: " + incoming.getPort());

			BufferedReader fileInfoReader = new BufferedReader(new InputStreamReader(incoming.getInputStream()));

			System.out.println("Reading from " + incoming.getLocalPort());

			for ( ; ; )
			{
				String str = fileInfoReader.readLine();

				System.out.println("read: " + str);
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
