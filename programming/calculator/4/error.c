#include <stdio.h>

#include "const.h"

int error()
{
	switch (errorcode)
	{
		case 1://������ ����
			printf("No money - no honey. No input - no movements. You are not in Kansas, boy...\n");
			break;
		case 2://������������ ���� ���������� (����� � ����������, ������� � ����������, ��������� � ����������
			printf("Reptile rum beats in your head, Johnny, and you can not correctly spell the names of old friends?\n");
			break;
		case 5://������ ���������, �� ���� ����������
			printf("When started, talk to the end, fella...\n");
			break;
		case 6://�������� ���������
			printf("You need to look after what you are saying, Johnny...\n");
			break;
		case 7://������ ������
			printf("Old wounds take their toll, and hands aren\'t hold by you, son?..\n");
			break;
	}

	return errorcode;
}
