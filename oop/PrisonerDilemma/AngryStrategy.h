#ifndef AngryStrategy_h
#define AngryStrategy_h

#include "Strategy.h"

class AngryStrategy: public Strategy
{
public:
	AngryStrategy();
	AngryStrategy(const AngryStrategy & other);
	virtual ~AngryStrategy();

	bool decision(const History & first, const History & second) const;
};


#endif // AngryStrategy
