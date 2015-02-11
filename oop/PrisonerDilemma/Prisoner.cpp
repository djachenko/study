

#include "Prisoner.h"

using namespace std;

Prisoner::Prisoner()
:strategy( factory.create("random") )
{
}

Prisoner::Prisoner(const string & name)
:strategy( factory.create(name) )
{
}

Prisoner::Prisoner(const Prisoner & other)
:strategy( factory.create( other.strategy->getName() ) ), history(other.history)
{
}

Prisoner::~Prisoner()
{
	delete strategy;
}

void Prisoner::setStrategy(const string & name)
{
	delete strategy;

	strategy = factory.create(name);
}

bool Prisoner::decide( const Prisoner & first, const Prisoner & second ) const
{
	return strategy->decision( first.getHistory(), second.getHistory() );
}

void Prisoner::remember(const bool decision)
{
	history.add(decision);
}

History & Prisoner::getHistory()
{
	return history;
}

const History & Prisoner::getHistory() const
{
	return history;
}
