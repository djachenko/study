package smtp;

import java.io.*;

public class Starter 
{
	public static void main(String[] args)
	{
		Client client = new Client();
		
		try(BufferedReader reader = new BufferedReader(new InputStreamReader(System.in)))
		{
			while (true)
			{
				System.out.print("Enter server address:\n> ");
               	String serverName = reader.readLine();

				try
				{
					client.connect(serverName);

					break;
				}
				catch(MySMTPException e)
				{
					System.out.println("Connection wasn't established, server returned an outor: " + e.getLocalizedMessage());
				}
			}

			while (true)
			{
				System.out.print("Enter username:\n> ");
               	String username = reader.readLine();

				System.out.print("Enter password:\n> ");
               	String password = reader.readLine();

				try
				{
					client.login(username, password);

					break;
				}
				catch (MySMTPException e)
				{
					System.out.println("Server returned an logging outor: " + e.getLocalizedMessage());
				}
			}

			while (true)
			{
				System.out.print("Enter your e-mail:\n> ");
				String email = reader.readLine();

				try
				{
					System.out.println(client.sendCommand("MAIL FROM: <" + email + '>'));

					break;
				}
				catch (MySMTPException e)
				{
					System.out.println("Server returned an logging outor: " + e.getLocalizedMessage());
				}
			}

			System.out.print("Enter number of recipients:\n> ");
			int number = Integer.parseInt(reader.readLine());

			for (int i = 1; i <= number; i++)
			{
				System.out.print("Enter email of recepient #" + i + ": ");
                String email = reader.readLine();

				try
				{
					client.sendCommand("RCPT TO:<" + email + '>');
				}
				catch (MySMTPException e)
				{
					System.out.println("Server returned an error: " + e.getLocalizedMessage());
					System.out.println("This recipient isn't valid and will be skipped.");
				}
			}


			System.out.print("Enter your message (only one line allowed):\n> ");
			StringBuilder message = new StringBuilder();

			while (true)
			{
				message.append(reader.readLine());

				if (!reader.ready())
				{
					break;
				}
			}

			try
			{
				client.sendCommand("DATA");
				client.sendCommand(message + "\n.");
			}
			catch (MySMTPException e)
			{
				System.out.println("Server returned sending error: " + e.getLocalizedMessage());
			}

			try
			{
				client.logout();
			}
			catch (MySMTPException e)
			{
				System.out.println("Server returned logging out error: " + e.getLocalizedMessage());
			}

			client.disconnect();
			
			System.out.println("Goodbye!");
		}

		catch (IOException e)
		{
			e.printStackTrace();
		}
	}	
}
