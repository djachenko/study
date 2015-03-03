package FrequencyCounter;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.*;

public class FrequencyCounter
{
	public static void main(String[] args)
	{
		Reader reader = null;

		try
		{
			reader = new InputStreamReader(new FileInputStream(args[0]));

			int c;
			StringBuilder word = new StringBuilder("");

			int counter = 0;

			final HashMap<String, Integer> holder = new HashMap<String, Integer>();

			for ( ; ; )
			{
				c = reader.read();

				if ( c != -1 && Character.isLetterOrDigit(c))
				{
					word.append((char)c);
				}
				else
				{
					String stringWord = new String(word);
					
					if ( holder.get( stringWord ) != null )
					{
						holder.put(stringWord, holder.get(stringWord) + 1);
					}
					else
					{
						holder.put(stringWord, 1);
					}

					counter++;

					word.setLength(0);
				}

				if ( c == -1 )
				{
					break;
				}
			}

			System.out.println(holder.size());

			ArrayList<String> sorter = new ArrayList<String>(holder.keySet());

			Collections.sort(sorter, new Comparator<String>()
			{
				@Override
				public int compare(String o1, String o2)
				{
					if (holder.get(o1) - holder.get(o2) < 0)
					{
						return 1;
					}

					return -1;
				}
			});

			for (int i = 0; i < sorter.size(); i++)
			{
				int k = holder.get(sorter.get(i));

				System.out.println(sorter.get(i) + ',' + k + ',' + (double)Math.round(((double)k)/counter*1000)/10 + '%');
			}
		}
		catch (IOException excptn)
		{
			System.err.println("Error while reading file " + excptn.getLocalizedMessage());
		}
		finally
		{
			if (null != reader)
			{
				try
				{
					reader.close();
				}
				catch (IOException excptn)
				{
					excptn.printStackTrace(System.err);
				}
			}
		}
	}
}