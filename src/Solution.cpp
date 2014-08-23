#include "Solution.h"
#include <iostream>

Solution::Solution(const int numGroups)
	: groupSize(10)
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
		score += group->score(groupSize);
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

void Solution::write(ostream& output)
{
	int i = 0;
	int friendLess = 0;
	for (auto group : groups)
	{
		output << "Group " << ++i;
		for (auto member : group->getMembers())
		{
			int friends = 0;
			output << "," << member->getLidNo();
			for (auto voorkeur : member->getVoorkeuren())
			{
				if (group->contains(voorkeur))
				{
					friends++;
				}
			}
			if (friends == 0)
				friendLess++;
		}
		output << endl;
	}
	output << "Score: " << score() << endl;
	output << "Friendless: " << friendLess << endl;
}

void Solution::setGroupSize(const int newSize) {
	groupSize = newSize;
}
