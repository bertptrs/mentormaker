#ifndef GROUP_H
#define GROUP_H
#include <set>
#include "Sjaars.h"

using namespace std;

class Group {
	private:
		set<const Sjaars *> members;

	public:
		static const int IDEAL_SIZE;

		Group();
		void insert(const Sjaars * sjaars);
		void remove(const Sjaars * sjaars);
		int size() const;
		int score() const;
		bool contains(const Sjaars * sjaars) const;
		const Sjaars * randomMember() const;
		void print() const;
		const set<const Sjaars*>& getMembers() const;
};

#endif
