package md5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class Server extends Thread
{
	private String string;
	private List<int[]> tasks;
	private static final int numberOfHandlers = 15;

	public Server(String string)
	{
		this.string = string;

		tasks = Collections.synchronizedList(new LinkedList<int[]>());

		int variationsCount = (int)Math.pow(string.length(), 4);

		int mod = (int)(variationsCount % numberOfHandlers);
		int div = variationsCount / numberOfHandlers;

		for (int i = 0; i < numberOfHandlers; i++)
		{
			tasks.add(new int[]{div * i, div * (i + 1)});
		}

		if (mod > 0)
		{
			tasks.add(new int[]{div * numberOfHandlers, variationsCount});
		}
	}

	@Override
	public void run()
	{
		try
		{
			byte [] hash = MessageDigest.getInstance("MD5").digest(string.getBytes());
			List<String> results = Collections.synchronizedList(new LinkedList<String>());

			try (ServerSocket socket = new ServerSocket(7854))
			{
				while (results.isEmpty())
				{
					new ClientHandler(socket.accept(), hash, string.length(), tasks, results).start();
					System.out.println("Handler started");
				}

				System.out.println("Is " + results.remove(0) + " your string?");
			}
		}
		catch (IOException | NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
	}

	public static void main(String[] args)
	{
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in)))
		{
			System.out.print("Enter string for encoding:\n> ");
			String string = reader.readLine();

			Server server = new Server(string);

			server.start();
			server.join();
		}
		catch (IOException | InterruptedException e)
		{
			e.printStackTrace();
		}
	}
}
