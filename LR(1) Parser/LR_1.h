#ifndef LR_1_h
#define LR_1_h

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;


class State;
class Edge;
class IItem
{
public:
	string name;
};


class Variable :public IItem
{
public:

	string short_name;

	Variable() {};
	Variable(string);
};

class Terminal : public IItem
{
public:
	Terminal() {};
	Terminal(string);
};

class Item
{
public:
	vector<IItem> expression;
	Item(string);
	Item(Item&);
	string getItemString();

};

class Rule
{
public:
	Variable leftSide;
	vector<Item> rightSide;

	Rule() {};
	Rule(string);
	Rule(Rule&);
	string getRuleString();
};

class LR1
{
public:
	Rule start;
	vector<Rule> rules;
	LR1(vector<string>, string);
	void printGrammer();
private:
	void createStartRule(string);
};


class StateItem
{
public :
	Rule rule;
	Terminal lookahead;
	StateItem() {};
	StateItem(Rule, Terminal);
};
class Edge
{
public:
	IItem cross;
	State target;
	Edge() {};
	Edge(IItem);
};

class State
{
public:
	vector<StateItem> rules;
	vector<Edge> edges;

};

class Automata
{
public:
	State start;
	vector<State> stats;
	LR1 context;
	Automata(LR1);

	
};




#endif