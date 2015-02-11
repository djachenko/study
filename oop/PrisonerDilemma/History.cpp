#include "History.h"

History::History()
{
}

History::History(const History & other)
:timeLine(other.timeLine)
{
}

History::~History()
{
}

bool History::operator[](int i)
{
	return timeLine[i];
}

const bool History::operator[](int i) const
{
	return timeLine[i];
}

void History::add(const bool decision)
{
	timeLine.push_back(decision);
}

History History::get(int size) const
{
	History result;

	for (int i = 0; i < timeLine.size() && i < size; i++)
	{
		result.add((*this)[i]);
	}

	return result;
}

bool History::last() const
{
	return timeLine.back();
}

int History::statistics() const
{
	int result = 0;

	for (std::vector<bool>::const_iterator i = timeLine.begin(); i != timeLine.end(); i++)
	{
		if (*i)
		{
			result++;
		}
		else
		{
			result--;
		}
	}

	return result;
}
