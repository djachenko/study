#include <stdio.h>
#include <stdlib.h>

#include "const.h"

void third_ai(int field[3][3])
{
	if (field[1][1] == 0)
	{
		field[1][1] = machine_turn;

		return;
	}
	else
	{
		int n = 0;

		int i;
		int j;

		for (i = 0; i < 3; i++)
		{
			for (j = 0;j < 3; j++)
			{
				if (field[i][j] == 0)
				{
					n++;
				}
			}
		}

		srand(time(NULL));

		int index = rand() % n;

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (field[i][j] == 0)
				{
					if (index == 0)
					{
						field[i][j] = machine_turn;

						return;
					}
					else
					{
						index--;
					}
				}
			}
		}
	}
}

void second_ai(int field[3][3], int sum_x[3], int sum_y[3], int sum_diag[2])
{
	int i;
	int j;

	for (i = 0; i < 3; i++)
	{
		if (sum_x[i] == 2)
		{
			for (j = 0; j < 3; j++)
			{
				if (field[i][j] == 0)
				{
					field[i][j] = machine_turn;

					return;
				}
			}
		}

		if (sum_y[i] == 2)
		{
			for (j = 0; j < 3; j++)
			{
				if (field[j][i] == 0)
				{
					field[j][i] = machine_turn;

					return;
				}
			}
		}
	}

	if (sum_diag[0] == 2)
	{
		for (i = 0; i < 3; i++)
		{
			if (field[i][i] == 0)
			{
				field[i][i] = machine_turn;

				return;
			}
		}
	}

	if (sum_diag[1] == 2)
	{
		for (i = 0; i < 3; i++)
		{
			if (field[i][2 - i] == 0)
			{
				field[i][2-i] = machine_turn;

				return;
			}
		}
	}

	third_ai(field);

	return;
}

void first_ai(int field[3][3])
{
	int i;
	int j;

	int sum_x[3] = {0};
	int sum_y[3] = {0};

	int sum_diag[2] = {0};

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			sum_x[i] += field[i][j];
			sum_y[i] += field[j][i];
		}

		sum_diag[0] += field[i][i];
		sum_diag[1] += field[i][2-i];
	}

	for (i = 0; i < 3; i++)
	{
		if (sum_x[i] == -2)
		{
			for (j = 0; j < 3; j++)
			{
				if (field[i][j] == 0)
				{
					field[i][j] = machine_turn;

					return;
				}
			}
		}

		if (sum_y[i] == -2)
		{
			for (j = 0; j < 3; j++)
			{
				if (field[j][i] == 0)
				{
					field[j][i] = machine_turn;

					return;
				}
			}
		}
	}

	if (sum_diag[0]==-2)
	{
		for (i=0;i<3;i++)
		{
			if (field[i][i]==0)
			{
				field[i][i]=machine_turn;

				return;
			}
		}
	}

	if (sum_diag[1]==-2)
	{
		for (i=0;i<3;i++)
		{
			if (field[i][2-i]==0)
			{
				field[i][2-i]=machine_turn;

				return;
			}
		}
	}

	second_ai(field,sum_x,sum_y,sum_diag);

	return;
}

int check(int field[3][3])
{
	int i;
	int j;

	int sum_x[3]={0};
	int sum_y[3]={0};

	int sum_diag[2]={0};

	int zeros=0;

	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			sum_x[i]+=field[i][j];
			sum_y[i]+=field[j][i];

			if (field[i][j]==0)
			{
				zeros++;
			}
		}

		sum_diag[0]+=field[i][i];
		sum_diag[1]+=field[i][2-i];
	}

	for (i=0;i<3;i++)
	{
		if (sum_x[i]==-3 || sum_y[i]==-3)
		{
			return 2;
		}

		if (sum_x[i]==3 || sum_y[i]==3)
		{
			return 1;
		}
	}

	for (i=0;i<2;i++)
	{
		if (sum_diag[i]==-3)
		{
			return 2;
		}

		if (sum_diag[i]==3)
		{
			return 1;
		}
	}

	if (zeros==0)
	{
		return 3;
	}

	return 0;
}

void out(int field[3][3], int figure[2][2])
{
	printf("   0 1 2\n");

	int i;
	int j;

	for (i=0;i<3;i++)
	{
		printf("%2d",i);

		for (j=0;j<3;j++)
		{
			switch (field[i][j])
			{
				case -1:
					putchar(figure[1][0]);
					putchar(figure[1][1]);

					break;
				case 0:
					putchar(' ');
					putchar(' ');

					break;
				case 1:
					putchar(figure[0][0]);
					putchar(figure[0][1]);

					break;
			}
		}

		printf("%d\n",i);
	}

	printf("   0 1 2\n");
}

int main()
{
	printf("Choose yor side:\n1:crosses\n2:circles\n3:random\n> ");

	int side=0;

	{
		char buffer[256]={0};

		while(1)
		{
			fgets(buffer,256,stdin);

			if (sscanf(buffer,"%d",&side)==1 && side>=1 && side <=3)
			{
				break;
			}

			printf("do it properly, my young padavan..\n> ");
		}
	}

	if (side==3)
	{
		srand(time(NULL));

		side=rand()%2;

		printf("you're playing with ");

		switch (side)
		{
			case 0:
				printf("crosses\n");

				break;				
			case 1:
				printf("circles\n");

				break;
		}
	}
	else
	{
		side--;
	}

	int figure[2][2]={{0}};

	figure[side][0]='>';
	figure[side][1]='<';
	figure[(side+1)%2][0]='(';
	figure[(side+1)%2][1]=')';

	int field[3][3]={{0}};

	if (side)
	{
		first_ai(field);
	}

	while (!check(field))
	{
		out(field,figure);

		printf("enter your turn:\n> ");

		char buffer[256]={0};

		int x;
		int y;

		while (1)
		{
			fgets(buffer,256,stdin);

			if (sscanf(buffer,"%d%d",&y,&x)==2 && (x>=0 && x<=2) && (y>=0 && y<=2) && !field[x][y])
			{
				field[x][y]=player_turn;

				break;
			}

			if (x>=0 && x<=2 && y>=0 && y<=2 && field[x][y])
			{
				printf("wtf?!! choose any empty cell, but not this\n> ");

				continue;
			}
				
			printf("do it properly, young padavan...\n> ");
		}

		if (check(field))
		{
			break;
		}

		first_ai(field);
	}

	out(field,figure);

	switch(check(field))
	{
		case 1:
			printf("you win\n");

			break;
		case 2:
			printf("you lose\n");

			break;
		case 3:
			printf("it's a draw\n");

			break;
	}

	return 0;
}
