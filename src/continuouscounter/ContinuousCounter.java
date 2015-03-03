package continuouscounter;

import java.io.IOException;
import java.net.*;
import java.util.*;

public class ContinuousCounter
{
	public static void main(String[] args)
	{
		try
		{
			InetAddress address = InetAddress.getByName("192.168.1.255");

			try (DatagramSocket socket = new DatagramSocket(5896))
			{
				System.out.println("port2: " + socket.getLocalPort());
				Map<InetAddress, Long> holder = Collections.synchronizedMap(new HashMap<InetAddress, Long>());
				Screamer screamer = new Screamer(socket, address);
				Listener listener = new Listener(socket, address, holder);
				Checker checker = new Checker(holder);

				screamer.start();
				listener.start();
				checker.start();

				checker.join();
				listener.join();
				screamer.join();
			}
			catch (SocketException e)
			{
				System.err.println("Error while binding: " + e.getLocalizedMessage());
				e.printStackTrace();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}

			System.out.println("Stopped");
		}
		catch (UnknownHostException e)
		{
			System.err.println("Error while binding address: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
    }
}

class Screamer extends Thread
{
	private InetAddress address = null;
	private DatagramSocket socket = null;

	Screamer(DatagramSocket socket, InetAddress address)
	{
		this.address = address;
		this.socket = socket;
	}

	public void run()
	{
		byte[] sendData = "ILIVE".getBytes();

		DatagramPacket flagPacket = new DatagramPacket(sendData, sendData.length, address, socket.getLocalPort());

		while (! this.isInterrupted() )
		{
			try
			{
				socket.send(flagPacket);

				sleep(1000);
			}
			catch (IOException e)
			{
				System.err.println("Error while sending flag packet: " + e.getLocalizedMessage());
				e.printStackTrace();
			}
			catch (InterruptedException e)
			{
				System.err.println("Error while sleeping: " + e.getLocalizedMessage());
				e.printStackTrace();
			}
		}
	}
}

class Listener extends Thread
{
	private DatagramSocket socket = null;
	private InetAddress address = null;
	private Map<InetAddress, Long> holder = null;

	Listener(DatagramSocket socket, InetAddress address, Map<InetAddress, Long> holder)
	{
		this.socket = socket;
		this.address = address;
		this.holder = holder;

		System.out.println("port: " + socket.getLocalPort());
	}


	public  void run()
	{
		byte[] receiveData = new byte[1024];

		System.out.println("socket: " + socket + " " + socket.getLocalPort());

		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length, address, socket.getLocalPort());

		for ( ; !this.isInterrupted(); )
		{
			try
			{
				socket.receive(receivePacket);

				InetAddress tempAddress = receivePacket.getAddress();

				if (!holder.containsKey(tempAddress))
				{
					System.out.println(tempAddress.toString() + " born.");
				}

				holder.put(tempAddress, System.currentTimeMillis());
			}
			catch (IOException e)
			{
				System.err.println("Listener");
				e.printStackTrace();
			}
		}
	}
}

class Checker extends Thread
{
	private Map<InetAddress, Long> holder = null;

	Checker(Map<InetAddress, Long> holder)
	{
		this.holder = holder;
	}

	public void run()
	{
		for ( ; !this.isInterrupted(); )
		{
			Long currentTime = System.currentTimeMillis();

			synchronized (holder)
			{
				for (InetAddress i : holder.keySet())
				{
					if (Math.abs(holder.get(i) - currentTime) > 5*1000)
					{
						System.out.println(i.toString() + " died...");

						holder.remove(i);
					}
				}
			}
		}
	}
}