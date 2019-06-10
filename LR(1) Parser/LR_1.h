#ifndef LR_1_h
#define LR_1_h

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;


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
	string getItemString();
};

class Rule
{
public:
	Variable leftSide;
	vector<Item> rightSide;

	Rule(string);
	string getRuleString();
};

class LR1
{
public:
	Variable start;
	vector<Rule> rules;
	LR1(vector<string>, string);
	void printGrammer();
};




#endif