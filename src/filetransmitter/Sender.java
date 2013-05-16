package filetransmitter;

import java.io.*;
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

			Boolean answer = Boolean.valueOf(new BufferedReader(new InputStreamReader(socket.getInputStream())).readLine());

			if (answer)
			{
				byte [] buffer = new byte[1024];

				FileInputStream input = new FileInputStream(sendingFile);

				while (input.available() > 0)
				{
					int read = input.read(buffer);

					outputStream.write(buffer, 0, read);
				}

				outputStream.flush();
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
