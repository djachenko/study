#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "tree.h"
#include "archiver.h"
#include "dearchiver.h"

struct list * codes[256];
struct list * buffer;
int buffer_size=0;

int main(int argc,char * argv[])
{
	int i;

	int task=1;//1 - архивировать, 0 - разархивировать
	char source_name[256]={0};//имя исходного файла
	char dest_name[256]={0};//имя целевого файла

	for (i=1;i<argc;i++)//разбор параметров
	{
		if (argv[i][0]=='-')//ключи
		{
			int l=strlen(argv[i]);
			int j;

			switch (argv[i][1])
			{
				case 'a':
					task=1;
					break;
				case 'd':
					task=0;
					break;
				case 'f':
					if (strncmp(argv[i]+1,"from=",5)==0)
					{
						if (!argv[i][6])
						{
							printf("Wrong argument of key \"-from\"\n");
							return 0;
						}

						strcpy(source_name,argv[i]+6);
						break;
					}
				case 't':
					if (strncmp(argv[i]+1,"to=",3)==0)
					{
						if (!argv[i][4])
						{
							printf("Wrong argument of key \"-to\"\n");
							return 0;
						}

						strcpy(dest_name,argv[i]+4);
						break;
					}
				default:
					printf("Error: wrong key \"%s\"\n",argv[i]);
					return 0;
			}
		}
		else
		{
			printf("Error: wrong key \"%s\"\n",argv[i]);
			return 0;
		}
	}

	if (!source_name[0])
	{
		printf("Enter name of source file, please: ");
		scanf("%s",source_name);
	}

	if (task)
	{
		archivize(source_name,dest_name);
	}
	else
	{
		dearchivize(source_name,dest_name);
	}

	return 0;
}
