#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int randInt(int max) {
	return rand() % max; // TODO: improve.
}

int main(int argc, const char **argv) {
	if (argc != 3) {
		cerr << "Invalid arguments!" << endl << endl
			<< "Usage:" << argv[0] << " member_count filename" << endl;
		return 1;
	}

	int lidCount = atoi(argv[1]);
	const char* filename = argv[2];
	
	ofstream out(filename);
	if (!out.good()) {
		cerr << "Could not open file for writing." << endl;
		return 2;
	}

	srand(time(NULL));

	for (int i = 0; i < lidCount; i++) {
		out << i << ",";
		out << ((rand() & 1) == 0 ? 'm' : 'v') << ",";
		out << randInt(lidCount) << ","
			<< randInt(lidCount) << "," << randInt(lidCount) << endl;
	}

	out.close();

	return 0;
}

