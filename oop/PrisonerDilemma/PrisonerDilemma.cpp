#include <vector>
#include <cctype>
#include <cstring>
#include <iostream>

#include "Prisoner.h"
#include "Factory.h"

#include "KindStrategy.h"
#include "AngryStrategy.h"
#include "RandomStrategy.h"

#include "Judge.h"

using namespace std;

enum modes
{
	nomode,
	detailed,
	fast,
	tournament
};

Factory factory;

int main(int argc, char ** args)
{
	factory.add<KindStrategy>("kind");
	factory.add<AngryStrategy>("angry");
	factory.add<RandomStrategy>("random");

	vector <string> names;

	int steps = 0;
	modes mode = nomode;
	string configs;

	for (int i = 1; i < argc; i++)
	{
		if ( args[i][0] != '-' )
		{
			if ( factory.exists(args[i]) )
			{
				names.push_back(args[i]);
			}
			else
			{
				cout << "Unknown strategy \"" << args[i] << "\". Go home, player, you're drunk." << endl;

				return 0;
			}

			continue;
		}
		else
		{
			if ( strncmp(args[i], "--steps=", 8) == 0 )
			{
				if ( steps != 0 )
				{
					cout << "Duplicate \"--steps\" parameter" << endl;

					return 0;
				}

				for ( int j = 8; args[i][j] || 8 == j; j++)
				{
					if (isdigit(args[i][j]))
					{
						steps = steps*10 + args[i][j]-'0';
					}
					else
					{
						cout << "Wrong \"--steps\" value" << endl;

						return 0;
					}
				}

				continue;
			}

			if ( strncmp(args[i], "--mode=", 7) == 0 )
			{
				if ( mode != nomode )
				{
					cout << "Duplicate \"--mode\" parameter" << endl;

					return 0;
				}

				if ( strcmp(args[i]+7,"detailed") == 0 )
				{
					mode = detailed;

					continue;
				}

				if ( 0 == strcmp(args[i]+7, "fast") )
				{
					mode = fast;

					continue;
				}

				if ( 0 == strcmp(args[i]+7, "detailed") )
				{
					mode = detailed;

					continue;
				}

				cout << "Wrong \"--mode\" value" << endl;

				return 0;
			}

			if ( 0 == strncmp(args[i], "--configs=", 10) )
			{
				if ( !configs.empty() )
				{
					cout << "Duplicate \"--configs\" parameter" << endl;

					return 0;
				}

				if ( 0 == args[i][10] )
				{
					cout << "Wrong \"--configs\" value" << endl;

					return 0;
				}

				configs = args[i]+10;

				cout << "Configs ok, but i don't know, how to work with them. I'm really sorry, man..." << endl;

				continue;
			}

			cout << "Unknown parameter \"" << args[i] << '\"' << endl;

			return 0;
		}
	}

	if ( names.size() < 3 )
	{
		cout << "Too few prisoners. You do not follow the plan!" << endl;

		return 0;
	}

	if ( nomode == mode )
	{
		if ( 3 == names.size() )
		{
			mode = detailed;
		}
		else
		{
			mode = tournament;
		}
	}

	if ( mode == tournament && names.size() < 3)
	{
		cout << "Unable to make tournament with less than three strategies. You have only " << names.size() << endl;

		return 0;
	}

	if ( 0 == steps )
	{
		steps = 64;
	}

	switch ( mode )
	{
		case fast:
		{
			cout << "Fast mode with " << steps << " steps..." << endl;

			Judge judge(names);

			judge.tick(steps);

			judge.printScore();

			return 0;
		}

		case detailed:
		{
			Judge judge(names);

			judge.play();

			return 0;
		}

		case tournament:
			for (int i = 0; i < names.size()-2; i++)
			{
				for (int j = i+1; j < names.size()-1; j++)
				{
					for (int k = j+1; k < names.size(); k++)
					{
						vector< string > subNames(3);

						subNames[0] = names[i];
						subNames[1] = names[j];
						subNames[2] = names[k];

						Judge judge(subNames);

						judge.tick(steps);

						cout << "In tournament iteration with strategies " << subNames[0] << ", " << subNames[1] << " and " << subNames[2];

						int min = -1;
						int mini = -1;

						for (int l = 0; l < 3; l++)
						{
							if (-1 == min || judge.getScore()[l] < min)
							{
								min = judge.getScore()[l];
								mini = l;
							}
						}

						cout << " won strategy " << subNames[mini] << '.' << endl;

						judge.printScore();
					}
				}
			}

			break;
		case nomode:
			cout << "WTF?!1" << endl;

			break;
	}


	return 0;
}
