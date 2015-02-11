#include <string>

#include "Judge.h"

using namespace std;

Judge::Judge( const vector< string > & names)
:prison(3), score(3, 0)
{
	for (int i = 0; i < 3; i++)
	{
		prison[i].setStrategy( names[i] );
	}

	vector <bool> key(3);
	vector <int> arg(3);

	for (int i = 0; i < 8; i++)
	{
		key[0] = i/4 == 1;
		key[1] = i%4/2 == 1;
		key[2] = i%2 == 1;

		if (i == 7)
		{
			arg[0] = 4;
			arg[1] = 4;
			arg[2] = 4;

			matrix[key] = arg;

			continue;
		}

		if (i == 0)
		{
			arg[0] = 1;
			arg[1] = 1;
			arg[2] = 1;

			matrix[key] = arg;

			continue;
		}

		if (i==1 || i==2 || i == 4)
		{
			arg[0] = 3;
			arg[1] = 3;
			arg[2] = 3;

			arg[ 2 - i/2  ] = 0;

			matrix[key] = arg;

			continue;
		}

		if (i==3 || i==5 || i==6)
		{
			arg[0] = 2;
			arg[1] = 2;
			arg[2] = 2;

			arg[ i/2 -1 ] = 5;

			matrix[key] = arg;

			continue;
		}
	}
}

Judge::~Judge()
{
}

void Judge::tick(int n)
{
	vector < bool > decisions(3, false);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			decisions[j] = prison[j].decide(prison[(j+1)%3], prison[(j+2)%3]);
		}

		for (int j = 0; j <3; j++)
		{
			score[j] += matrix[decisions][j];
		}

		for (int j = 0; j < 3; j++)
		{
			prison[j].remember(decisions[j]);

			if (decisions[j])
			{
				cout << "C ";
			}
			else
			{
				cout << "D ";
			}
		}

		cout << endl;
	}
}

void Judge::play()
{
	string command;
	bool error;
	bool tick;//не нужно. но, если удалить, ничего понятно не будет.
	int n;

	for ( ; ; )
	{
		error = false;
		tick = false;
		n = 0;

		command.clear();

		for ( ; command.empty() ; )
		{
			cout << "> ";

			getline(cin, command);
		}

		int quitPos = command.find("quit");
		int tickPos = command.find("tick");

		if ( quitPos != string::npos )
		{
			if ( command.find("quit", quitPos+1) == string::npos )
			{
				break;
			}
			else
			{
				error = true;
			}
		}

		if ( !error && tickPos != string::npos )
		{
			if ( command.find("tick", tickPos+1) == string::npos )
			{
				tick = true;

				for ( int i = tickPos+5; isdigit( command[i] ); i++)
				{
					n = n*10 + command[i]-'0';
				}

				if ( n == 0 )
				{
					n = 1;
				}
			}
			else
			{
				error = true;
			}
		}

		if ( tick )
		{
			this->tick(n);

			printScore();

			continue;
		}

		if ( error )
		{
			cout << "Sorry, prisoners didn't understand your French..." << endl;
		}
	}
}

const vector<int> & Judge::getScore() const
{
	return score;
}

void Judge::printScore() const
{
	cout << "Score:" << endl;
	cout << "First:" << '	' << score[0] << endl;
	cout << "Second:" << '	' << score[1] << endl;
	cout << "Third:" << '	' << score[2] << endl;
}
