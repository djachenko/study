package smtp;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Client
{
	private static final int DEFAULT_PORT = 25;
	
	private Socket socket = null;
	private BufferedWriter writer = null;
	private BufferedReader reader = null;
	
	String connect(String host, int port) throws MySMTPException, IOException
	{
		System.out.println("connecting to \"" + host + "\" to port " + port);

		socket = new Socket(host, port);
		
		reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
		
		return readAnswer();
	}
	
	String connect(String host) throws MySMTPException, IOException
	{
		return connect(host, DEFAULT_PORT);
	}
	
	public void disconnect() throws IOException, MySMTPException
	{
		if (socket != null && socket.isConnected())
		{
			socket.close();
			
			socket = null;
			
			reader = null;
			writer = null;
		}
	}
	
	String sendCommand(String command) throws IOException, MySMTPException
	{
		writer.write(command + '\n');
		writer.flush();
		
		return readAnswer();
	}
	
	String readAnswer() throws MySMTPException, IOException
	{
		String[] answer = reader.readLine().split(" ", 2);
		
		if (answer[0].charAt(0) == '5')
		{
			throw new MySMTPException("Server has returned an error: " + answer[1]);
		}
		else
		{
			return answer[1];
		}
	}

	void logout() throws MySMTPException, IOException
	{
		sendCommand("QUIT");
	}
}
