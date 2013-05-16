package md5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.List;

public class ClientHandler extends Thread
{
	private Socket socket;
	private byte [] hash;
	private int length;
	private List<int[]> tasks;
	private List<String> results;

	public ClientHandler(Socket socket, byte [] hash, int length, List<int[]> tasks, List<String> results)
	{
		this.socket = socket;
		this.hash = hash;
		this.length = length;
		this.tasks = tasks;
		this.results = results;
	}

	@Override
	public void run()
	{
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		     PrintWriter writer = new PrintWriter(socket.getOutputStream()))
		{
			writer.println(length);
			writer.println(new String(hash));

			for ( ; ;)
			{
				int [] task;

				synchronized (tasks)//because it's not atomic
				{
					if (tasks.isEmpty())
					{
						task = null;
					}
					else
					{
						task = tasks.remove(0);
					}
				}

				if (task == null)
				{
					writer.println("STOP");

					return;
				}
				else
				{
					writer.println("WORK");
					writer.println(task[0]);
					writer.println(task[1]);
					writer.flush();

					System.out.println("Task sent");

					switch (reader.readLine())
					{
						case "SUCCESS":
							String result = reader.readLine();

							tasks.clear();
							results.add(result);

							return;
						case "UNSUCCESS":
							break;
					}
				}
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
