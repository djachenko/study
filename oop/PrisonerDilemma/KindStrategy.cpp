#include "KindStrategy.h"

KindStrategy::KindStrategy()
:Strategy("kind")
{
}

KindStrategy::KindStrategy(const KindStrategy & other)
:Strategy(other)
{
}

KindStrategy::~KindStrategy()
{
}

bool KindStrategy::decision(const History & first, const History & second) const
{
	return true;
}
