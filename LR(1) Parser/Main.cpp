
#include "LR_1.h"



int main(int argc, const char* argv[]) {


	//#1
	string R2 = "<E> : <T> | <E> + <T>";
	string R3 = "<T> : i | ( <E> )";

	//#2
	/*string R2 = "<E> : <B> <B>";
	string R3 = "<B> : c <B> | d";*/

	//#3
	/*string R2 = "<S> : a <A> a | <A>";
	string R3 = "<A> : a";*/

	//#4
	/*string R2 = "<S> : <L> = <R> | <R>";
	string R3 = "<L> : * <R> | x";
	string R4 = "<R> : <L>";*/

	vector<string> gr = { R2, R3 }; // #1 #2 #3
	//vector<string> gr = { R2, R3,R4 }; //#4
	LR1 LR(gr, "<E>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	table t(automata);
	t.print();

	//#2
	/*vector<string> input = { "c", "c", "d", "d" };
	t.parse(input);
	input = { "c", "c","c", "c", "d", "d" };
	t.parse(input);
	input = { "w", "d" };
	t.parse(input);
	input = { "d", "d" };
	t.parse(input);*/

	//#1
	vector<string> input = { "(", "i", "+", "i", ")" };
	t.parse(input);
	cout << "\nPress enter for exit...";
	getchar();
	return 0;
}
