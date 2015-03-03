import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;


public class Task 
{
	public static void main(String[] args) 
	{
		try 
		{
			File output = new File("output.txt");
			
			new PrintWriter(output).println("NOBODY LOSES");	
		} 
		catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		}
	}
}
