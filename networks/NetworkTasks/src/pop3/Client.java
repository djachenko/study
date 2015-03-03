package pop3;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Client
{
	private static final int DEFAULT_PORT = 110;
	
	private Socket socket = null;
	private BufferedWriter writer = null;
	private BufferedReader reader = null;
	
	String connect(String host, int port) throws MyPOP3Exception, IOException
	{
		socket = new Socket(host, port);
		
		reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
		
		return readAnswer();
	}
	
	String connect(String host) throws MyPOP3Exception, IOException
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
	
	String sendCommand(String command) throws IOException, MyPOP3Exception
	{
		writer.write(command + '\n');
		writer.flush();
		
		return readAnswer();
	}
	
	String readAnswer() throws MyPOP3Exception, IOException
	{
		String answer = reader.readLine();
		
		if (answer.startsWith("-ERR"))
		{
			throw new MyPOP3Exception("Server has returned an error: " + answer.replace("-ERR ", ""));
		}
		else
		{
			return answer;
		}
	}
	
	void login(String name, String password) throws MyPOP3Exception, IOException
	{
		System.out.println(sendCommand("USER " + name));
		System.out.println(sendCommand("PASS " + password));
	}
	
	void logout() throws MyPOP3Exception, IOException
	{
		sendCommand("QUIT");
	}
	
	int countMessages() throws MyPOP3Exception, IOException
	{
		return Integer.parseInt(sendCommand("STAT").split(" ")[1]);
	}
	
	String getMessage(int i) throws MyPOP3Exception, IOException
	{
		sendCommand("RETR " + i);
		
		String answer;
		StringBuilder message = new StringBuilder();
		
		while (true)
		{
			answer = readAnswer();
			
			if (answer.equals("."))
			{
				break;
			}
			
			message.append(answer);
		}
		
		return String.valueOf(message);
	}
	
	List<String> getAllMessages() throws MyPOP3Exception, IOException
	{
		List<String> result = new ArrayList<>();
		
		for (int i = 1; i <= countMessages(); i++)
		{
			result.add(getMessage(i));
		}
		
		return result;
	}
}
