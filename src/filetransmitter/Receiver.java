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

			new ReceiverThread(socket.accept()).start();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}

class ReceiverThread extends Thread
{
	Socket incoming = null;

	public ReceiverThread(Socket socket)
	{
		incoming = socket;
	}

	@Override
	public void run()
	{
		try
		{
			String name;
			long size;

			InputStream inputStream = incoming.getInputStream();

			{
				BufferedReader in = new BufferedReader(new InputStreamReader(inputStream));

				name = in.readLine();
				size = Long.parseLong(in.readLine());
			}

			File receivingFile = new File(name);

			PrintWriter out = new PrintWriter(incoming.getOutputStream());

			if (receivingFile.exists())
			{
				System.out.println("Receiving file exists. Cancelling.");

				out.write(Boolean.FALSE.toString());
				out.flush();

				return;
            }
			else
			{
				out.write(Boolean.TRUE.toString());
				out.flush();

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

					fileOutput.write(buffer, 0, read);
				}
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
