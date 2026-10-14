#include "Strategy.h"

Strategy::Strategy(const string & name)
:name(name)
{
}

Strategy::Strategy(const Strategy & other)
{
}

Strategy::~Strategy()
{
}

const string & Strategy::getName() const
{
	return name;
}
