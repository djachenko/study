#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>

#include "Game.h"

using namespace std;

Game::Game()
{
}

Game::Game(int x, int y)
:field(x, y)
{
}

Game::Game(const Game & other)
:field(other.field), rules(other.rules), name(other.name)
{
}

Game::~Game()
{
}

void Game::read(const string & name)
{
	ifstream input;

	if ( !name.empty() )
	{
		input.open(name.c_str());
	}
	else
	{
		ifstream baseList;

		baseList.open("Life.config");

		vector<string> bases;

		string name;

		cout << "base " <<  endl;

		for ( ; baseList.good(); )
		{
			baseList >> name;

			cout << "name: " << name << endl;

			bases.push_back(name);
		}

		srand( time(NULL) );

		input.open( bases[ rand() % bases.size() ].c_str() );
	}

	read(input);
}

void Game::read(istream & input)
{
	string str;

	getline(input, str);//descriptor

//NAME

	input >> str;//#N

	input.get();

	getline(input,name);

	input >> str;//#R

//RULES

	for (int i=0; i<=9; i++)
	{
		rules[false][i] = survival;
		rules[true][i] = death;
	}

	char c;

	for ( ; c!='\n'; )
	{
		c=input.get();

		actions action;

		switch (c)
		{
			case 'B':
				action=birth;

				break;
			case 'S':
				action=survival;

				break;
			default:
				if (c>='0' && c<='9')
				{
					rules[birth!=action][c-'0']=action;
				}
		}
	}

	cout << name << endl;
//FIELD

	field.read(input);
}

void Game::tick(int n)
{
	for ( ; n; n--)
	{
		for (int i=0; i<field.getSizeX(); i++)
		{
			for (int j=0; j<field.getSizeY(); j++)
			{
				field[i][j].changeState( rules[ field[i][j].alive() ][ field.countNeighbours(i, j) ] );
			}
		}

		field.update();
	}
}

void Game::dump(const string & name)
{
	ofstream output;

	output.open(name.c_str());

	output << "#Life 1.06" << endl;

	output << "#N " << name << endl;

	output << "#R B";

	for (int i=0; i<=9; i++)
	{
		if (rules[false][i]==birth)
		{
			output << i;
		}
	}

	output << "/S";

	for (int i=0; i<=9; i++)
	{
		if (rules[true][i]==survival)
		{
			output << i;
		}
	}

	output << endl;

	for (int i=0; i<field.getSizeX(); i++)
	{
		for (int j=0; j<field.getSizeY(); j++)
		{
			if (field[i][j].alive())
			{
				output << i << ' ' << j << endl;
			}
		}
	}
}

void Game::print() const
{
	field.print();
}

void Game::help() const
{
	cout << "HELP:" << endl;

	cout << "1. For dumping game state into file <filename> enter \"dump <filename>\"" << endl;
	cout << "2. For counting N iterations enter \"tick <N>\" (by default N=1)" << endl;
	cout << "3. For help enter \"help\"" << endl;
	cout << "4. For finishing game enter \"exit\"" << endl;
}

void Game::init(int & argc, char ** c_args)
{
	bool offline=false;

	int iterations=0;
	string output;
	string input;

	vector< string > args( argc );

	for (int i=0; i<argc; i++)//conversion from char *'s to strings
	{
		args[i]=c_args[i];
	}

	try
	{
		for (int i=1; i<argc; )
		{
			if ( 0 == args[i].compare(0, 13, "--iterations=") )
			{
				if ( iterations )
				{
					throw duplicateIValue;
				}

				for (int j=13; j<args[i].length(); j++)
				{
					if ( isdigit( args[i][j] ) )
					{
						iterations=iterations*10+args[i][j]-'0';
					}
					else
					{
						throw wrongIValue;
					}
				}

				i++;

				offline=true;

				continue;
			}

			if ( 0 == args[i].compare("-i") )
			{
				if (iterations)
				{
				throw duplicateIValue;
				}

				i++;

				if (i==argc)
				{
					throw wrongIValue;
				}

				for (int j=0; j<args[i].length(); j++)
				{
					if ( isdigit( args[i][j] ) )
					{
						iterations=iterations*10+args[i][j]-'0';
					}
					else
					{
						throw wrongIValue;
					}
				}

				i++;

				offline=true;

				continue;
			}

			if ( 0 == args[i].compare(0, 9, "--output=") )
			{
				if ( !output.empty() )
				{
					throw duplicateOValue;
				}

				output=args[i].substr(9);

				i++;

				offline = true;

				continue;
			}

			if ( 0 == args[i].compare("-o") )
			{
				if ( !output.empty() )
				{
					throw duplicateOValue;
				}

				i++;

				if (i==argc)
				{
					throw wrongOValue;
				}

				output=args[i];

				i++;

				offline = true;

				continue;
			}

			if ( i==argc-1 )
			{
				input=args[i];

				i++;
			}
			else
			{
				throw wrongParameter;
			}
		}

		this->read( input );

		if (offline)
		{
			if ( 0==iterations )
			{
				throw wrongIValue;
			}

			if ( output.empty() )
			{
				throw wrongOValue;
			}

			this->tick(iterations);

			this->dump(output);

			return;
		}
	}
	catch (GameExceptions excptn)
	{
		switch (excptn)
		{
			case wrongIValue:
				cout << "Wrong iteration parameter." << endl;

				break;
			case duplicateIValue:
				cout << "Iteration parameter should be defined only once" << endl;

				break;
			case wrongOValue:
				cout << "Wrong output file name." << endl;

				break;
			case duplicateOValue:
				cout << "Output file should be defined only once" << endl;

				break;
			case wrongParameter:
				cout << "This program doesn't know such parameters. Call your language teacher, system administrator or psychiatrist - only in this order." << endl;

				break;
			default:
				cout << "WTF?!!" << endl;
		}

		return;
	}

	this->print();

	while ( 1 )
	{
		string command;
	
		cout << "> ";

		cin >> command;

		if ( !command.compare("tick") || !command.compare("t") )
		{
			char val[256];

			cin.getline(val, 256, '\n');//pot_error

			string value=val;

			if ( !value.empty() )
			{
				this->tick( atoi( value.c_str() ) );
			}
			else
			{
				this->tick();
			}

			this->print();

			continue;
		}

		if ( !command.compare("dump") )
		{
			string value;

			cin >> value;

			this->dump(value);

			continue;
		}

		if ( !command.compare("help") )
		{
			this->help();

			continue;
		}

		if ( !command.compare("exit") )
		{
			return;
		}

		cout << "Unknown command" << endl;
	}
}
