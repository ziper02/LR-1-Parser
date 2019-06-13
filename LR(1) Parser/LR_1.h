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
	friend bool operator!=(const IItem& lhs, const IItem& rhs) {
		return (lhs.name != rhs.name);
	}
	bool isExist(vector<IItem>) const;
	bool isExist(vector<IItem>);
	bool isTerminal();
	bool operator < (const IItem& x) const;
	bool operator > (const IItem& x) const;
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
	LR1 context;
	StateItem() {};
	StateItem(Rule, Terminal,LR1);
	vector<IItem>getBeta();
	
	IItem getnext();
	bool exist(vector<StateItem>);
	bool operator==(const StateItem& x) const;
	bool operator<(const StateItem& x) const;
};

class State
{
public:
	vector<StateItem> rules;
	State() = default;
	void clousre(LR1);
	void delta();
	bool operator==(const State& x) const;
};

class Automata
{
public:
	State start;
	vector<State> stats;
	map<pair<State, IItem>, State> getState;
	LR1 context;
	Automata(LR1);
	bool stateExist(State);
	
};




#endif