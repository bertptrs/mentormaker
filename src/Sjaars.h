#ifndef SJAARS_H
#define SJAARS_H
#include <set>
#include <map>

using namespace std;

enum geslacht_t {
	MAN = 0,
	VROUW = 1
};

class Sjaars {
	private:
		int lidNo;
		geslacht_t geslacht;
		set<int> voorkeurIds;
		set<const Sjaars*> voorkeuren;
		bool geplaatst;

	public:
		Sjaars(int lidNo, geslacht_t geslacht, const set<int>& voorkeuren);

		bool isGeplaatst() const;
		void setGeplaatst(bool geplaatst = true);
		bool laadVoorkeuren(const map<int, Sjaars*>& sjaarzen);
		int getLidNo() const;
		geslacht_t getGeslacht() const;

		const set<const Sjaars *>& getVoorkeuren() const;

};

#endif
