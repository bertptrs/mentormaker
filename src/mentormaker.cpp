#include <iostream>
#include "Solver.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "No input file specified." << endl << endl
			<< "Usage: " << argv[0] << " input_filename" << endl;

		return 1;
	}
	Solver s;
	s.readInput(argv[1]);

	return 0;
}
