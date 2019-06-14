
#include "LR_1.h"



int main(int argc, const char* argv[]) {

	//string R2 = "<E> : <T> | <E> + <T>";
	//string R3 = "<T> : i | ( <E> )";
	string R2 = "<S> : a <A> a | <A>";
	string R3 = "<A> : a";
	vector<string> gr = { R2, R3 };

	LR1 LR(gr, "<S>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	return 0;
}
