#ifndef Cell_h
#define Cell_h

enum actions
{
	birth,
	survival,
	death
};

class Cell
{
	private:
		int state;
	public:
		Cell();
		Cell(const Cell & other);
		~Cell();

		void born();
		void die();
		void update();

		bool alive() const;
		bool dead() const;

		void print() const;

		int getState() const;
		void changeState(const actions action);
};

#endif //Cell_h
