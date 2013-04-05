package filetransmitter;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Receiver
{
	public static void main(String[] args)
	{
		try
		{
			ServerSocket socket = new ServerSocket(7686);

			Socket incoming = socket.accept();

			String name;
			long size;

			InputStream inputStream = incoming.getInputStream();

			{
				Scanner in = new Scanner(inputStream);

				name = in.nextLine();
				size = in.nextLong();

				System.out.println(name + ' ' + size);
			}

			File receivingFile = new File(name);

			PrintWriter out = new PrintWriter(incoming.getOutputStream());

			if (receivingFile.exists())
			{
				System.out.println("Receiving file exists. Cancelling.");

				out.write(new Boolean(false).toString());
				out.flush();

				return;
            }

			if (receivingFile.getUsableSpace() < size)
			{
				System.err.println("Not enough disc quota. Cancelling");

				out.write(new Boolean(false).toString());
				out.flush();

				return;
			}

			out.write(new Boolean(true).toString());
			out.flush();

			receivingFile.createNewFile();
			FileOutputStream fileOutput = new FileOutputStream(receivingFile);

			byte [] buffer = new byte[1024];

			for (int i = 0; i < size; )
			{
				int read = inputStream.read(buffer);

				if (read == -1)
				{
					System.err.println("Sender closed connection. Cancelling");

					receivingFile.delete();

					return;
				}

				i += read;

				fileOutput.write(buffer);
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
