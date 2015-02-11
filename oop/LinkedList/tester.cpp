#include <iostream>
#include <assert.h>
#include "LinkedList.h"

using namespace std;

int main()
{
	LinkedList a;

	cout << "empty: " << a.empty() << '\n';

	a.push_front(2);
	a.push_front(5);
	a.push_back(6);
	a.push_back(10);
	a.push_front(7);
	a.push_front(6);

	cout << "strt\n";
	
	for (LinkedList::iterator i=a.begin(); i!=a.end(); i++)
	{
		cout << *i << ' ';
	}
	//!test -

	cout << '\n';
	
	cout << "front: " << a.front() << '\n';

	cout << "back: " << a.back() << '\n';

	cout << "contains 2: " << a.contains(2) << '\n';

	cout << "contains 3: " << a.contains(3) << '\n';

	cout << "count 7: " << a.count(7) << '\n';
	cout << "count 3: " << a.count(3) << '\n';
	cout << "count 6: " << a.count(6) << '\n';

	cout << "size: " << a.size() << '\n';
	cout << "empty: " << a.empty() << '\n';

	for (LinkedList::iterator i=a.begin(); i!=a.end(); i++)
	{
		a.insert(i,1);
	}

	for (LinkedList::iterator i=a.begin(); i!=a.end(); i++)
	{
		cout << *i << ' ';	
	}

	cout << '\n';

//	a.removeAll(1);

	a+=11;

	cout << "added\n";

	for (LinkedList::iterator i=a.begin(); i!=a.end(); i++)
	{
		cout << *i << ' ';	
	}

	cout << '\n';

	LinkedList::iterator x=a.begin();

//if(x==x)cout<<(&x); else cout<<"!!!";

	for (LinkedList::iterator i=a.begin(); i!=a.end(); i++)
	{
		i.print();
	}

	return 0;
}
