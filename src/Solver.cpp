#include "Solver.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <limits>
#include <iostream>
#include <algorithm>

Solver::Solver() {
}

Solver::~Solver() {
	for (auto sjaarzenPaar: sjaarzen) {
		delete sjaarzenPaar.second;
	}
	for (auto solution : solutions) 
	{
		delete solution;
	}
}

bool Solver::readInput(const char* input_filename) {
	ifstream input(input_filename);

	if (!input.good()) {
		cerr << "Could not open input file for reading." << endl;
		return false;
	}

	int lidNo;

	while ((input >> lidNo)) {
		int voorkeuren[] = {-1, -1, -1};
		assert(input.get() == ',');
		geslacht_t geslacht = (input.get() | 32) == 'm' ? MAN : VROUW;
		
		for (int i = 0; i < 3 && input.get() != '\n'; i++) {
			input >> voorkeuren[i];
		}

		Sjaars* sjaars = new Sjaars(lidNo, geslacht, voorkeuren[0], voorkeuren[1], voorkeuren[2]);
		assert(sjaarzen[lidNo] == NULL);
		sjaarzen[lidNo] = sjaars;
	}

	for (auto sjaarzenPaar: sjaarzen) {
		sjaarzenPaar.second->laadVoorkeuren(sjaarzen);
	}
	input.close();

	return true;
}

int Solver::bestScore() const
{
	int best = numeric_limits<int>::min();
	Solution * bestSolution = NULL;
	for (auto solution : solutions) {
		int score = solution->score();
		if (score > best)
		{
			best = score;
			bestSolution = solution;
		}
	}
	if (bestSolution != NULL)
	{
		bestSolution->print();
	}
	return best;
}

void Solver::save(const char * filename)
{
	// First, sort the solutions by score.
	sort(solutions.begin(), solutions.end(),
			[](Solution* a, Solution* b) -> bool {
			return a->score() > b->score();
			});

	// Now save.
	ofstream output(filename);
	assert(output.good());
	for (auto solution : solutions)
	{
		solution->write(output);
		output << endl;
	}
	output.close();
}
