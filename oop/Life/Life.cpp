#include <string>

#include "Game.h"

using namespace std;

int main(int argc, char ** args)
{
	Game life(40, 25);

	life.init(argc, args);

	return 0;
}
