#ifndef Strategy_h
#define Strategy_h

#include <string>

#include "History.h"

using namespace std;

class Strategy
{
private:
	string name;
public:
	Strategy(const string & name);
	Strategy(const Strategy & other);
	virtual ~Strategy();

	virtual bool decision(const History & first, const History & second) const = 0;
	const string & getName() const;
};

#endif //Strategy_h
