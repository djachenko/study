package md5;

import java.io.*;
import java.net.Socket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

public class Client extends Thread
{
	private static final String HOST = "localhost";
	private static final int PORT = 7854;
	private static final char [] GENES = {'A', 'C', 'G', 'T'};

	private static String codeToString(int code, int length)
	{
		StringBuilder string = new StringBuilder();

		for (int i = 0; i < length; i++)
		{
			string.append(GENES[code % 4]);
			code /= 4;
		}

		return String.valueOf(string.reverse());
	}

	@Override
	public void run()
	{
		try (Socket socket = new Socket(HOST, PORT))
		{
			BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

			MessageDigest MD5Counter = MessageDigest.getInstance("MD5");

			int length = Integer.parseInt(reader.readLine());

			byte [] hash = reader.readLine().getBytes();

			for ( ; ; )
			{
				switch (reader.readLine())
				{
					case "STOP":
						return;
					case "WORK":
						int start = Integer.parseInt(reader.readLine());
						int end = Integer.parseInt(reader.readLine());

						System.out.println("Start: " + start);
						System.out.println("End: " + start);

						for (int code = start; code < end; code++)
						{
							String temp = codeToString(code, length);

							//MD5Counter.update(temp.getBytes());
							byte [] temphash = MD5Counter.digest(temp.getBytes());

							System.out.println(code + " " + temp + ' ' + hash + ' ' + temphash);

							if (Arrays.equals(hash, temphash))
							{
								writer.println("SUCCESS");
								writer.println(temp);
								writer.flush();

								return;
							}
						}

						writer.println("UNSUCCESS");
						writer.flush();
				}
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
			while (true)
			{
				new Client().start();

				reader.readLine();
            }
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
