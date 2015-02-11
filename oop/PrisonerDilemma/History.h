#ifndef History_h
#define History_h

#include <vector>

class History
{
	private:
	std::vector<bool> timeLine;

	public:
	History();
	History(const History & other);
	virtual ~History();

	bool operator[](int i);
	const bool operator[](int i) const;

	void add(const bool decision);

	History get(int size) const;
	bool last() const;

	int statistics() const;
};

#endif //History_h
