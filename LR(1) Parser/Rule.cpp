
#include "LR_1.h"


Rule::Rule(Variable var,Item item)
{
	this->leftSide = var;
	this->rightSide = item;
}

 vector<Rule> Rule::createRule(string rule)
{
	 vector<Rule> rules;
	Variable leftSide;
	int i = 0, startIndex;
	bool flag = true;
	string temp = "";
	while (flag)
	{
		temp.append(string(1, rule.at(i)));
		i++;
		if (rule.at(i) == '>')
			flag = false;
	}
	temp.append(string(1, rule.at(i)));
	leftSide = Variable(temp);
	i = i + 4;
	startIndex = i;
	for (i; i < rule.size(); i++)
	{
		if (rule.at(i) == '|')
		{
			temp = rule.substr(startIndex, i - startIndex - 1);
			startIndex = i + 1;
			rules.push_back(Rule(leftSide,Item(temp)));
		}
	}
	temp = rule.substr(startIndex, i - startIndex + 1);
	rules.push_back(Rule(leftSide, Item(temp)));
	return rules;
}


string Rule::getRuleString()
{
	string temp = "";
	temp.append(leftSide.name);
	temp.append(" --> ");
	temp.append(rightSide.getItemString());
	return temp;
}

//Rule::Rule(const Rule &rule)
//{
//	this->leftSide = rule.leftSide;
//	this->rightSide = rule.rightSide;
//}


bool Rule::includeTerminal()
{
	for(IItem temp : this->rightSide.expression)
	{
		if(Terminal * p = dynamic_cast<Terminal*>(&temp))
		{
			if (!((*p) == Terminal("e")))
				return true;
		}
	}
	return false;
}


bool Rule::operator==(const Rule& x) const
{
	int xsize = x.rightSide.expression.size();
	if (xsize != rightSide.expression.size())
		return false;
	if (x.leftSide != leftSide)
		return false;
	for (int i = 0; i < x.rightSide.expression.size(); i++)
		if (x.rightSide.expression.at(i) != rightSide.expression.at(i))
			return false;
	return true;
}