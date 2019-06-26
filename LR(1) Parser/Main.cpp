
#include "LR_1.h"



int main(int argc, const char* argv[]) {


	//#1--- TRUE-------------------------------------------------------------------------------------------
	/*string R2 = "<E> : <T> | <E> + <T>";
	string R3 = "<T> : i | ( <E> )";
	vector<string> gr = { R2, R3};
	LR1 LR(gr, "<E>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	table t(automata);
	t.print();
	vector<string> input = { "(", "i", "+", "i", ")" };
	t.parse(input);*/

	//#2--- TRUE-------------------------------------------------------------------------------------------
	/*string R2 = "<E> : <B> <B>";
	string R3 = "<B> : c <B> | d";
	vector<string> gr = { R2, R3 };
	LR1 LR(gr, "<E>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	table t(automata);
	t.print();
	vector<string> input = { "c", "c", "d", "d" };
	t.parse(input);
	input = { "c", "c","c", "c", "d", "d" };
	t.parse(input);
	input = { "w", "d" };
	t.parse(input);
	input = { "d", "d" };
	t.parse(input);*/

	//#3--- TRUE-------------------------------------------------------------------------------------------
	/*string R2 = "<S> : a <A> a | <A>";
	string R3 = "<A> : a";
	vector<string> gr = { R2, R3 };
	LR1 LR(gr, "<S>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	table t(automata);
	t.print();*/


	//#4--- TRUE-------------------------------------------------------------------------------------------
	/*string R2 = "<S> : <L> = <R> | <R>";
	string R3 = "<L> : * <R> | x";
	string R4 = "<R> : <L>";
	vector<string> gr = { R2, R3,R4 };
	LR1 LR(gr, "<S>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	table t(automata);
	t.print();
	vector<string> input = { "x", "=", "*", "x" };
	t.parse(input);
	input = { "x", "=", "x" };
	t.parse(input);
	input = { "x", "=","=", "x" };
	t.parse(input);
	input = { "x", "x","=", "x" };
	t.parse(input);
	input = { "x", "=","x", "x" };
	t.parse(input);*/

	//#5--- FALSE-------------------------------------------------------------------------------------------
	string R2 = "<S> : <C> <C>";
	string R3 = "<C> : x <C> | x";
	vector<string> gr = { R2, R3 };
	LR1 LR(gr, "<S>");
	LR.printGrammer();
	Automata automata(LR);
	automata.printAutomata();
	table t(automata);
	t.print();


	cout << "\nPress enter for exit...";
	getchar();
	return 0;
}
