#ifndef Judge_h
#define Judge_h

#include <vector>
#include <map>
#include <string>

#include <iostream>

#include "Prisoner.h"

using namespace std;

class Judge
{
private:
	vector<Prisoner> prison;
	vector < int > score;
	map < vector<bool>, vector<int> > matrix;
public:
	Judge( const vector< string > & names );
	virtual ~Judge();

	void tick(int n = 1);

	void play();

	const vector <int> & getScore() const;
	void printScore() const;
};

#endif // Judge_h
