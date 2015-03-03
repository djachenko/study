package speedmeter;

import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server
{
	public static void main(String[] args)
	{
		try (ServerSocket socket = new ServerSocket(7651))
		{
			System.out.println("Server started");

			while (true)
			{
				new Thread(new ServerThread(socket.accept())).start();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}

class ServerThread implements Runnable
{
	private Socket socket = null;
	private static final int BUFFERSIZE = 256 * 1024;
	private static final int TRIES = 25;

	public ServerThread(Socket incoming)
	{
		socket = incoming;
	}

	@Override
	public void run()
	{
		try
		{
			System.out.println("ServerThread started");

			InputStream input =  socket.getInputStream();
			PrintStream output = new PrintStream(socket.getOutputStream());

			byte [] buffer = new byte[BUFFERSIZE];

			for (int i = 0; i < TRIES; i++)
			{
				System.out.print(i + "... ");

				int size = input.read(buffer);
				long end = System.currentTimeMillis();

				if (size == -1)
				{
					break;
				}

				System.out.println(size);

				output.println(size);
				output.println(end);
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}

