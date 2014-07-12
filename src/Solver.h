#ifndef SOLVER_H
#define SOLVER_H
#include "Sjaars.h"
#include "Solution.h"
#include <map>
#include <vector>

using namespace std;

class Solver {
	protected:
		map<int, Sjaars*> sjaarzen;
		vector<Solution*> solutions;

	public:
		Solver();
		virtual ~Solver();

		bool readInput(const char* input_filename);
		int bestScore() const;
		virtual void solve() = 0;
		void save(const char*);
};

#endif
