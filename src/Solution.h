#ifndef SOLUTION_H
#define SOLUTION_H
#include "Group.h"
#include <vector>

using namespace std;

class Solution {
	private:
		vector<Group*> groups;
	
	public:
		Solution(const int numGroups);
		~Solution();
		int score() const;
		int groupCount() const;
		Group* getGroup(const int index) const;
		void print() const;
};

#endif