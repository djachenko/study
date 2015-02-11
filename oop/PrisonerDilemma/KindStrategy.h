#ifndef KindStrategy_h
#define KindStrategy_h

#include "Strategy.h"

class KindStrategy: public Strategy
{
public:
	KindStrategy();
	KindStrategy(const KindStrategy & other);
	virtual ~KindStrategy();

	bool decision(const History & first, const History & second) const;
};


#endif // KindStrategy
