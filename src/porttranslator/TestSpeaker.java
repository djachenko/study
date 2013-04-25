package porttranslator;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

public class TestSpeaker
{
	public static void main(String[] args)
	{
		try(Socket socket = new Socket(args[0], Integer.parseInt(args[1])))
		{
			PrintWriter out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

			String string;

			while (true)
			{
				string = in.readLine();

				if (string == null)
				{
					break;
				}
				else
				{
					out.println(string);
					out.flush();
				}
			}
		}
		catch (UnknownHostException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
