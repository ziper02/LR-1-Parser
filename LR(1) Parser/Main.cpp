
#include "LR_1.h"



int main(int argc, const char* argv[]) {

	string R2 = "<E> : <T> | <E> + <T>";
	string R3 = "<T> : i | ( <E> )";
	vector<string> gr = { R2, R3 };

	LR1 LR(gr, "<E>");
	LR.printGrammer();
	Automata automata(LR);
	return 0;
}
