#ifndef RandomStrategy_h
#define RandomStrategy_h

#include "Strategy.h"

class RandomStrategy: public Strategy
{
public:
	RandomStrategy();
	RandomStrategy(const RandomStrategy & other);
	virtual ~RandomStrategy();

	bool decision(const History & first, const History & second) const;
};


#endif // RandomStrategy

