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

			Socket incoming = socket.accept();

			InputStream in = incoming.getInputStream();
			BufferedReader fileInfoReader = new BufferedReader(new InputStreamReader(incoming.getInputStream()));

			System.out.println("Reading");

			for ( ; ; )
			{
				System.out.println(fileInfoReader.readLine());
			}
//
//			System.out.println("reading");
//			String name = fileInfoReader.readLine();
//			int size = Integer.parseInt(fileInfoReader.readLine());
//			System.out.println("read");
//
//			File receivingFile = new File(name);
//
//			PrintStream out = new PrintStream(incoming.getOutputStream());
//
//			if (receivingFile.exists())
//			{
//				System.out.println("File exists, sorry");
//
//				out.println(new Boolean(false).toString());
//			}
//			else if (receivingFile.getUsableSpace() < size)
//			{
//				System.out.println("Not enough mana");
//
//				out.println(new Boolean(false).toString());
//			}
//			else
//			{
//				System.out.println("starting...");
//
//				out.println(new Boolean(true).toString());
//
//				receivingFile.createNewFile();
//
//				FileOutputStream receivingFileStream = new FileOutputStream(receivingFile);
//				byte [] buffer = new byte[1024];
//
//				for (int i = size; i >= 1024; i--)
//				{
//					in.read(buffer);
//					receivingFileStream.write(buffer);
//				}
//
//				if (size % 1024 > 0)
//				{
//					buffer = new byte[size % 1024];
//
//					in.read(buffer);
//					receivingFileStream.write(buffer);
//				}
//			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
