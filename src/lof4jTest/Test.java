/*
package lof4jTest;

import org.apache.log4j.*;

import java.io.IOException;

public class Test
{
	public static void main(String[] args) throws IOException
	{
		BasicConfigurator.configure();

		Logger logger = Logger.getLogger(Test.class.getClass());
		FileAppender appender = new FileAppender(new SimpleLayout(), "output.txt");

		new PatternLayout().

		logger.addAppender(appender);

		logger.info("Hello world!");
		logger.error("Error!", new Exception("An exception"));
	}
}
*/