package filetransmitter;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Socket;

public class Sender
{
	public static void main(String[] args)
	{
		try
		{
			Socket socket = new Socket("localhost", 7686);

			PrintWriter writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

			System.out.println("Speaking " + socket.isConnected() + ' ' + socket.getPort() + ' ' + socket.getLocalPort());

			//socket.getOutputStream().write(new byte[1024]);

			System.out.println("sent");

			return;
			                     /*
			BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));

			for ( ; ; )
			{
				System.out.print("> ");

				String str = stdin.readLine();

				System.out.println("sending " + str);
				writer.println(str);
			}                      */
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
