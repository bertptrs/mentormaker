#ifndef SOLVER_H
#define SOLVER_H
#include "Sjaars.h"
#include <map>

using namespace std;

class Solver {
	private:
		map<int, Sjaars*> sjaarzen;

	public:
		Solver();
		~Solver();

		bool readInput(const char* input_filename);
};

#endif
