#include <iostream>
#include "Solver.h"
#include "HillClimbSolver.h"
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
	const char * inFile;
	const char * outFile;
	string input;
	string output;
	int groepNum;
	if (argc < 4) {
		cerr << "Mentormaker called without arguments." << endl;
		cerr << "Input file? ";
		cin >> input;
		inFile = input.c_str();
		cerr << "Output file? ";
		cin >> output;
		outFile = output.c_str();
		cerr << "Group size? ";
		cin >> groepNum;
	} else {
		inFile = argv[1];
		outFile = argv[2];
		groepNum = atoi(argv[3]);
	}
	srand (time(NULL));

	Solver* solver = new HillClimbSolver();
	solver->setGroupSize(groepNum);
	solver->readInput(inFile);
	solver->solve();

	cout << "Best result: " << solver->bestScore() << endl;

	solver->save(outFile);

	delete solver;

	return 0;
}
