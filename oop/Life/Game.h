#ifndef Game_h
#define Game_h

#include <string>
#include <map>

#include "Field.h"

class Game
{
	private:
		Field field;
		std::map<bool, std::map<int, actions> > rules;
		std::string name;
	public:
		Game();
		Game(int x, int y);
		Game(const Game & other);
		virtual ~Game();

		void read(const string & name);
		void read(istream & input);

		void tick(int n=1);
		void dump(const string & name);
		void print() const;
		void help() const;

		void init(int & argc, char ** args);
};

enum GameExceptions
{
	wrongIValue,//wrong value of -i or --iterations parameter key
	duplicateIValue,//redefinition
	wrongOValue,//wrong value of -o or --output parameter key
	duplicateOValue,//redefinition
	wrongParameter,//not last parameter is not a key

};

#endif //Game_h
