#ifndef Field_h
#define Field_h

#include <vector>
#include <string>

#include "Cell.h"

using namespace std;

class Field
{
	private:
		vector< vector< Cell > > table;
		int sizeX;
		int sizeY;
	public:
		Field();
		Field(int x, int y);
		Field(const Field & other);
		virtual ~Field();

		vector<Cell> & operator[](int i);
		const vector<Cell> & operator[](int i) const;

		void read(const char * name=NULL);
		void read(istream & input);
		void print() const;

		int getSizeX() const;
		int getSizeY() const;

		int countNeighbours(int x, int y);

		void resize(const int newX, const int newY);

		void update();
};

#endif //Field_h
