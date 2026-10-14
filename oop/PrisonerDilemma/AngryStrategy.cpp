#include "AngryStrategy.h"

using namespace std;

AngryStrategy::AngryStrategy()
:Strategy("angry")
{
}

AngryStrategy::AngryStrategy(const AngryStrategy & other)
:Strategy(other)
{
}

AngryStrategy::~AngryStrategy()
{
}

bool AngryStrategy::decision(const History & first, const History & second) const
{
	return false;
}
