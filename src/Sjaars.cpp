#include "Sjaars.h"
#include <iostream>

Sjaars::Sjaars(int lidNo, geslacht_t geslacht, int voorkeur1, int voorkeur2, int voorkeur3) :
	lidNo(lidNo),
	geslacht(geslacht),
	geplaatst(false)
{
	voorkeurIds[0] = voorkeur1;
	voorkeurIds[1] = voorkeur2;
	voorkeurIds[2] = voorkeur3;
}

bool Sjaars::isGeplaatst() const {
	return geplaatst;
}

void Sjaars::setGeplaatst(bool geplaatst_a) {
	geplaatst = geplaatst_a;
}

bool Sjaars::laadVoorkeuren(const map<int, Sjaars*>& sjaarzen) {
	for (int id : voorkeurIds) {
		if (id < 0)
			continue;

		if (sjaarzen.find(id) == sjaarzen.end()) {
			cerr << "Sjaars with non-existant preference." << endl;
			return false;
		} else {
			voorkeuren.insert((*(sjaarzen.find(id))).second);
		}
	}

	return true;

}

const set<const Sjaars *>& Sjaars::getVoorkeuren() const {
	return voorkeuren;
}

int Sjaars::getLidNo() const
{
	return lidNo;
}

geslacht_t Sjaars::getGeslacht() const
{
	return geslacht;
}
