#include <iostream>
#include "Solver.h"
#include "HillClimbSolver.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "No input file specified." << endl << endl
			<< "Usage: " << argv[0] << " input_filename" << endl;

		return 1;
	}
	srand (time(NULL));

	Solver* solver = new HillClimbSolver();
	solver->readInput(argv[1]);
	solver->solve();

	cout << "Best result: " << solver->bestScore() << endl;

	delete solver;

	return 0;
}
