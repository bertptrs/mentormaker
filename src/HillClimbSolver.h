#ifndef HILLCLIMBSOLVER_H
#define HILLCLIMBSOLVER_H

#include "Solver.h"
#include "Solution.h"
#include <vector>

using namespace std;

class HillClimbSolver : public Solver
{
	private:
		static const int SOLUTION_COUNT;
		static const int ITERATION_COUNT;

		void initSolve();
		void randomSwap(const Solution*);
	protected:

	public:
		HillClimbSolver();
		virtual ~HillClimbSolver();
		virtual void solve();
};

#endif
