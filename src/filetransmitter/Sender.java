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
			File sendingFile = new File(args[0]);

			if (!sendingFile.exists())
			{
				System.err.println("Unable to send non-existing file");

				return;
			}

			Socket socket = new Socket("192.168.1.7", 7686);

			OutputStream outputStream = socket.getOutputStream();

			{
				PrintWriter out = new PrintWriter(outputStream);

				out.println(sendingFile.getName());
				out.println(sendingFile.length());

				out.flush();
			}

			byte [] buffer = new byte[1024];

			FileInputStream input = new FileInputStream(sendingFile);

			while (input.available() > 0)
			{
				input.read(buffer);

				outputStream.write(buffer);
			}

			outputStream.flush();

			System.out.println("Successfully sent");
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
