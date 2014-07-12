#include "Solution.h"
#include <iostream>

Solution::Solution(const int numGroups)
{
	for (int i = 0; i < numGroups; i++) {
		groups.push_back(new Group);
	}
}

Solution::~Solution()
{
	for (auto group : groups)
	{
		delete group;
	}
}

int Solution::score() const
{
	int score = 0;

	for (const Group * group : groups) {
		score += group->score();
	}

	return score;
}

int Solution::groupCount() const
{
	return groups.size();
}

Group* Solution::getGroup(const int index) const
{
	return groups[index];
}

void Solution::print() const
{
	for (unsigned i = 0; i < groups.size(); i++)
	{
		cout << "Group " << i << ":" << endl;
		groups[i]->print();
		cout << endl;
	}
}
