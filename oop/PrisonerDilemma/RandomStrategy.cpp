#include <cstdlib>
#include <ctime>

#include "RandomStrategy.h"

RandomStrategy::RandomStrategy()
:Strategy("random")
{
}

RandomStrategy::RandomStrategy(const RandomStrategy & other)
:Strategy(other)
{
}

RandomStrategy::~RandomStrategy()
{
}

bool RandomStrategy::decision(const History & first, const History & second) const
{
	return rand()%2 == 0;
}
