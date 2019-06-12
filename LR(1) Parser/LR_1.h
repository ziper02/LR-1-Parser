#ifndef LR_1_h
#define LR_1_h


#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>


using namespace std;


class State;

class IItem
{
public:
	string name;
	virtual  ~IItem() {};
	friend bool operator==(const IItem& lhs, const IItem& rhs) {
		return (lhs.name == rhs.name);
	}
	bool isTerminal();
	bool operator < (const IItem& x) const;

};


class Variable :public IItem
{
public:

	string short_name;
	virtual  ~Variable() {};
	Variable() {};
	Variable(string);

};

class Terminal : public IItem
{
public:
	Terminal() {};
	virtual ~Terminal() {};
	Terminal(string);
};

class Item
{
public:
	vector<IItem> expression;
	Item(){};
	Item(string);
	Item(const Item&);
	string getItemString();

};

class Rule
{
public:
	Variable leftSide;
	Item rightSide;

	Rule() {};
	virtual ~Rule() {};
	Rule(Variable,Item);
	static vector<Rule>createRule(string);
	//Rule(const Rule&);
	bool includeTerminal();
	string getRuleString();
};

class LR1
{
public:
	Rule start;
	vector<Rule> rules;
	LR1(){};
	LR1(vector<string>, string);
	void printGrammer();
	set<Terminal> First(vector<IItem>);
	set<Variable> eps();
	map<IItem,set<Terminal>> First();
private:
	void createStartRule(string);
};

class Edge
{
public:
	IItem cross;
	State *target;
	Edge() {};
	Edge(IItem);
};

class StateItem
{
public:
	Rule rule;
	int sperator;
	Terminal lookahead;
	StateItem() {};
	StateItem(Rule, Terminal);
	vector<IItem>getBeta();
	bool operator < (const StateItem& x) const;
};

class State
{
public:
	set<StateItem> rules;
	vector<Edge> edges;
	State() {};
	void clousre(LR1);
	bool StateItemExist(StateItem);
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