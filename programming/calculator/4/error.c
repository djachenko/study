#include <stdio.h>

#include "const.h"

int error()
{
	switch (errorcode)
	{
		case 1://пустой ввод
			printf("No money - no honey. No input - no movements. You are not in Kansas, boy...\n");
			break;
		case 2://неправильный ввод переменной (знаки в переменной, функция в переменной, константа в переменной
			printf("Reptile rum beats in your head, Johnny, and you can not correctly spell the names of old friends?\n");
			break;
		case 5://пустое выражение, но есть переменная
			printf("When started, talk to the end, fella...\n");
			break;
		case 6://странное выражение
			printf("You need to look after what you are saying, Johnny...\n");
			break;
		case 7://пустые скобки
			printf("Old wounds take their toll, and hands aren\'t hold by you, son?..\n");
			break;
	}

	return errorcode;
}
