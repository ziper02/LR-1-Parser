
#include "LR_1.h"



int main(int argc, const char* argv[]) {

	/*string R2 = "<E> : <T> | <E> + <T>";
	string R3 = "<T> : i | ( <E> )";*/

	string R2 = "<E> : <B> <B>";
	string R3 = "<B> : c <B> | d";

	/*string R2 = "<S> : a <A> a | <A>";
	string R3 = "<A> : a";*/

	/*string R2 = "<S> : <L> = <R> | <R>";
	string R3 = "<L> : * <R> | x";
	string R4 = "<R> : <L>";*/
	vector<string> gr = { R2, R3 };

	LR1 LR(gr, "<E>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	table t(automata);
	t.print();
	return 0;
}
