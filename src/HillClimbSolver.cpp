#include "HillClimbSolver.h"
#include <cmath>
#include <cstdlib>

const int HillClimbSolver::SOLUTION_COUNT = 10;
const int HillClimbSolver::ITERATION_COUNT = 100000;

HillClimbSolver::HillClimbSolver()
{
}

void HillClimbSolver::initSolve()
{
	int groups = (int) round(sjaarzen.size() / (double) groupSize);
	// Allocate a few solutions
	for (int i = 0; i < SOLUTION_COUNT; i++)
	{
		Solution * solution = new Solution(groups);
		for (auto& sjaarzenPaar : sjaarzen)
		{
			Group* group = solution->getGroup(rand() % solution->groupCount());
			group->insert(sjaarzenPaar.second);
		}
		solutions.push_back(solution);
	}
}

void HillClimbSolver::solve()
{
	initSolve();
	for (int i = 0; i < ITERATION_COUNT; i++)
	{
		for (Solution* solution : solutions)
		{
			randomSwap(solution);
		}
	}
}

void HillClimbSolver::randomSwap(const Solution* solution)
{
	const int score = solution->score();

	Group * group1;
	Group * group2;
	do  {
		group1 = solution->getGroup(rand() % solution->groupCount());
	} while (group1->size() == 0);

	do {
		group2 = solution->getGroup(rand() % solution->groupCount());
	} while (group1 == group2);

	const Sjaars * member = group1->randomMember();

	group1->remove(member);
	group2->insert(member);

	if (solution->score() < score)
	{
		// This is worse, change it back.
		group1->insert(member);
		group2->remove(member);
	}
}

HillClimbSolver::~HillClimbSolver()
{
}
