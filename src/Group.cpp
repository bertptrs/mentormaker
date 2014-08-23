#include "Group.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Group::Group()
{
}

void Group::insert(const Sjaars * sjaars)
{
	members.insert(sjaars);
}

void Group::remove(const Sjaars * sjaars)
{
	members.erase(members.find(sjaars));
}

int Group::size() const
{
	return members.size();
}

int Group::score(const int groupSize) const
{
	int score = 0;

	for (const Sjaars * sjaars : members)
	{
		int friends = 0;

		for (const Sjaars * voorkeur : sjaars->getVoorkeuren())
		{
			friends += contains(voorkeur);
		}

		// Reward friends in a group
		score += 4 * friends;
		// Punish groups with lone wolves.
		if (friends == 0)
			score -= 50;
	}

	// punish bad group sizes.
	score -= (int) pow(abs(size() - groupSize), 2);

	return score;
}

bool Group::contains(const Sjaars * sjaars) const
{
	return members.count(sjaars) == 1;
}

const Sjaars * Group::randomMember() const
{
	int index = rand() % size();

	auto it = members.begin();
	advance(it, index);

	return *it;
}

void Group::print() const
{
	int rate = 0;
	int friends = 0;
	int noFriends = 0;
	for (auto sjaars : members)
	{
		cout << 0 << sjaars->getLidNo() << " ("
			<< (sjaars->getGeslacht() == MAN ? 'm' : 'v') << ") :";
		bool hasFriend = false;
		for (auto voorkeur : sjaars->getVoorkeuren())
		{
			if (contains(voorkeur)) hasFriend = true, friends++;

			cout << '\t' << voorkeur->getLidNo();
		}
		if (!hasFriend)
			noFriends++;
		rate += sjaars->getGeslacht() == MAN;
		cout << endl;
	}
	cout << "Size: " << size() << ". Connections: " << friends;
	cout << " Friendless: " << noFriends;
	cout << ". M/V: " << ((double) rate) / (size() - rate) << endl;
}

const set<const Sjaars*>& Group::getMembers() const
{
	return members;
}
