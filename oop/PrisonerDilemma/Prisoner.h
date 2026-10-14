#ifndef Prisoner_h
#define Prisoner_h

#include <string>

#include "Strategy.h"
#include "History.h"
#include "Factory.h"

class Prisoner
{
private:
	Strategy * strategy;
	History history;

public:
	Prisoner();
	Prisoner(const string & name);
	Prisoner(const Prisoner & other);
	virtual ~Prisoner();

	void setStrategy( const string & name );

	bool decide( const Prisoner & first, const Prisoner & second ) const;
	void remember(const bool decision);

	History & getHistory();
	const History & getHistory() const;
};

#endif //Prisoner_h
