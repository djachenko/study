#include "LongNumber.h"
#include <string.h>
#include <ctype.h>

int check(char *string)
{
	int len = strlen(string);

	if (0 == len)
	{
		return len;
	}

	int index = 0;

	if ('-' == string[0])
	{
		index++;
	}

	for (; index < len; index++)
	{
		if ('.' == string[index])
		{
			index++;
			break;
		}

		if (!isdigit(string[index]))
		{
			return 0;
		}
	}

	for (; index < len; index++)
	{
		if (!isdigit(string[index]))
		{
			return 0;
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	LongNumber a = parse("1000.5");
	LongNumber b = parse("0.0");

	print(a);

//	print(divide(a, b, 1));
	print(mul(a, b));

	return 0;
}
