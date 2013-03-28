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

	public ServerThread(Socket incoming)
	{
		socket = incoming;

		System.out.println("ServerThread started");
	}

	@Override
	public void run()
	{
		try
		{
			InputStream input =  socket.getInputStream();

			PrintStream output = new PrintStream(socket.getOutputStream());

			byte [] buffer = new byte[1024];

			int size = input.read(buffer);
			long end = System.currentTimeMillis();

			output.println(size);
			output.println(end);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}

