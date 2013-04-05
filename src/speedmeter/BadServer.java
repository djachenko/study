package speedmeter;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class BadServer 
{
	public static void main(String[] args)
	{
		try (ServerSocket socket = new ServerSocket(7653))
		{
			System.out.println("Server started");

			while (true)
			{
				new Thread(new BadServerThread(socket.accept())).start();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}

class BadServerThread implements Runnable
{
	private Socket socket = null;
	private static final int BUFFERSIZE = 16*1024 * 1024;
	private static final int TRIES = 25;

	public BadServerThread(Socket incoming)
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

			byte [] buffer = new byte[BUFFERSIZE];
			long [] starts = new long[TRIES];
			long [] ends = new long[TRIES];

			for (int i = 0; i < TRIES; i++)
			{
				int size = 0;
				int received = 0;

				starts[i] = System.currentTimeMillis();

				while (size < buffer.length && received != -1)
				{
					received = input.read(buffer, size, buffer.length - size);

					size += received;
				}

				ends[i] = System.currentTimeMillis();

				if (size == -1)
				{
					break;
				}
			}

			double averageTime = 0;

			for (int i = 0; i < TRIES; i++)
			{
				averageTime += ends[i] - starts[i];
			}

			averageTime /= TRIES;
			averageTime /= 1000;//converting to seconds

			double speed = (BUFFERSIZE / 1024) / averageTime;//converting BUFFERSIZE to Kbytes

			System.out.println("Speed is " + speed + "Kbytes/second");
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
