package filetransmitter;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Socket;

public class Sender
{
	public static void main(String[] args)
	{
		try(FileInputStream sendingFile = new FileInputStream(args[0]))
		{
			Socket socket = new Socket("localhost", 7686);

			byte [] buffer = new byte[1024];

			OutputStream out = socket.getOutputStream();

			PrintWriter writer = new PrintWriter(socket.getOutputStream());

			System.out.println("Speaking " + socket.isConnected() + ' ' + socket.getPort() + ' ' + socket.getLocalPort());

			BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));

			for ( ; ; )
			{
				System.out.print("> ");
				writer.println(stdin.readLine());
			}

//			System.out.println("Sending");

//			writer.println(args[0]);
//			writer.println(sendingFile.available());
//
//			if ( new Boolean( new BufferedReader( new InputStreamReader( socket.getInputStream() ) ).readLine() ) )
//			{
//				for ( int i = 0 ; sendingFile.available() >= buffer.length; i++)
//				{
//					System.out.println(i);
//					sendingFile.read(buffer);
//					out.write(buffer);
//				}
//
//				if (sendingFile.available() > 0)
//				{
//					buffer = new byte[sendingFile.available()];
//
//					sendingFile.read(buffer);
//					out.write(buffer);
//				}
//			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
