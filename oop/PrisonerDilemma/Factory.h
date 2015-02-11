#ifndef Factory_h
#define Factory_h

#include <map>//creators
#include <string>//names
#include <cstdlib>//srand
#include <ctime>//time

#include "Strategy.h"

#include "KindStrategy.h"
#include "AngryStrategy.h"
#include "RandomStrategy.h"

class AbstractCreator
{
public:
	virtual Strategy * create() const = 0;
};

template <class C>
class Creator: public AbstractCreator
{
public:
	Strategy * create() const
	{
		return new C();
	}
};

class Factory
{
private:
	typedef std::map<std::string, AbstractCreator*> FactoryMap;
	FactoryMap creators;

public:
	Factory()
	{
		srand(time(NULL));
	}
	virtual ~Factory()
	{
	}

	template <class C>
	void add(const std::string & name)
	{
		typename FactoryMap::iterator i = creators.find(name);

		if ( i == creators.end() )
		{
				creators[name] = new Creator<C>();
		}
	}

	Strategy * create(const std::string & name) const
	{
		FactoryMap::const_iterator i = creators.find(name);

		if ( i != creators.end() )
		{
			return i->second->create();
		}

		return 0;
	}

	bool exists(const string & name) const
	{
		return creators.find(name) != creators.end();
	}
};

extern Factory factory;

#endif
