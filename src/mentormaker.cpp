#include <iostream>
#include "Solver.h"
#include "HillClimbSolver.h"
#include <string>

using namespace std;

int main(int argc, char** argv) {
	const char * inFile;
	const char * outFile;
	string input;
	string output;
	if (argc < 3) {
		cerr << "Mentormaker called without arguments." << endl;
		cerr << "Input file? ";
		cin >> input;
		inFile = input.c_str();
		cerr << "Output file? ";
		cin >> output;
		outFile = output.c_str();
	} else {
		inFile = argv[1];
		outFile = argv[2];
	}
	srand (time(NULL));

	Solver* solver = new HillClimbSolver();
	solver->readInput(inFile);
	solver->solve();

	cout << "Best result: " << solver->bestScore() << endl;

	solver->save(outFile);

	delete solver;

	return 0;
}
