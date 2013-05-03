package pop3;

import java.io.IOException;
import java.util.*;

class Message
{
	private String body;

	protected Message(String body)
	{
		this.body = body;
	}

	public String getBody()
	{
		return body;
	}

	protected Message getMessage(int i) throws IOException
	{
		String response = new String();//sendCommand("RETR " + i);
		Map<String, List<String>> headers = new HashMap<String, List<String>>();
		String headerName = null;

// process headers
		while ((response = readResponseLine()).length() != 0)
		{
			if (response.startsWith("\t"))
			{
				continue; //no process of multiline headers
			}

			int colonPosition = response.indexOf(":");
			headerName = response.substring(0, colonPosition);

			String headerValue;

			if (headerName.length() > colonPosition)
			{
				headerValue = response.substring(colonPosition + 2);
			}
			else
			{
				headerValue = "";
			}

			List<String> headerValues = headers.get(headerName);

			if (headerValues == null)
			{
				headerValues = new ArrayList<String>();
				headers.put(headerName, headerValues);
			}

			headerValues.add(headerValue);
		}
// process body

		StringBuilder bodyBuilder = new StringBuilder();

		while (!(response = readResponseLine()).equals("."))
		{
			bodyBuilder.append(response + "\n");
		}

		return new Message(headers, bodyBuilder.toString());
	}


}
/**/