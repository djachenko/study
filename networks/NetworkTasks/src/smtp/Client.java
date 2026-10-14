package smtp;

import com.sun.org.apache.xml.internal.security.utils.Base64;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

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

		sendCommand("EHLO localhost");
		
		return readAnswer();
	}
	
	String connect(String host) throws MySMTPException, IOException
	{
		return connect(host, DEFAULT_PORT);
	}
	
	public void disconnect() throws IOException
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
		StringBuilder answer = new StringBuilder();

		while (true)
		{
			answer.append(reader.readLine());

			if (!reader.ready())
			{
				break;
			}
		}

		if (answer.charAt(0) == '5')
		{
			throw new MySMTPException("Server has returned an error: " + answer);
		}
		else
		{
			return String.valueOf(answer);
		}
	}

	void login(String username, String password) throws IOException, MySMTPException
	{
		sendCommand("AUTH LOGIN");
		sendCommand(Base64.encode(username.getBytes()));
		sendCommand(Base64.encode(password.getBytes()));
	}

	void logout() throws MySMTPException, IOException
	{
		sendCommand("QUIT");
	}
}
