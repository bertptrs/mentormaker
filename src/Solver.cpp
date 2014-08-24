#include "Solver.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <limits>
#include <iostream>
#include <algorithm>
#include <set>

Solver::Solver()
: groupSize(10) {
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

bool Solver::readInput(const char* input_filename)
{
	ifstream input(input_filename);

	if (!input.good()) {
		cerr << "Could not open input file for reading." << endl;
		return false;
	}

	int lidNo;

	while ((input >> lidNo)) {
		set<int> voorkeuren;
		assert(input.get() == ',');
		geslacht_t geslacht = (input.get() | 32) == 'm' ? MAN : VROUW;
		
		while (input.peek() != '\r' && input.get() != '\n') {
			int voorkeur;
			input >> voorkeur;
			if (input.fail()) {
				// Repeating commas or something.
				continue;
			}
			voorkeuren.insert(voorkeur);
		}

		Sjaars* sjaars = new Sjaars(lidNo, geslacht, voorkeuren);
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

void Solver::setGroupSize(const int newSize) {
	groupSize = newSize;
	for (auto solution : solutions) {
		solution->setGroupSize(newSize);
	}
}
