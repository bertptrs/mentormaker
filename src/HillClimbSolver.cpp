#include "HillClimbSolver.h"
#include <cmath>

const int HillClimbSolver::SOLUTION_COUNT = 10;
const int HillClimbSolver::ITERATION_COUNT = 100000;

HillClimbSolver::HillClimbSolver()
{
}

void HillClimbSolver::initSolve()
{
	int groups = (int) round(sjaarzen.size() / (double) Group::IDEAL_SIZE);
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
	int rand1 = rand() % solution->groupCount();
	int rand2 = rand() % solution->groupCount();
	const int score = solution->score();

	if (rand1 == rand2)
		return;

	Group * group1 = solution->getGroup(rand1);
	Group * group2 = solution->getGroup(rand2);

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
