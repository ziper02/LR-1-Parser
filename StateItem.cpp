#include "lr(1) parser/LR_1.h"

StateItem::StateItem(Rule rule, Terminal terminal)
{
	this->rule = rule;
	this->lookahead = terminal;
	sperator = 0;
}


vector<IItem> StateItem::getBeta()
{
	vector<IItem> result;
	int i;
	for(i=sperator+1;i<this->rule.rightSide.expression.size();i++)
	{
		if (rule.rightSide.expression.at(i).isTerminal() == false)
			break;
	}
	for (; i < this->rule.rightSide.expression.size(); i++)
		result.push_back(rule.rightSide.expression.at(i));
	return result;
}

bool StateItem::exist(vector<StateItem> x)
{
	if (find(x.begin(), x.end(), this) == x.end())
		return false;
	else
		return true;
}



bool StateItem::operator == (const StateItem& x) const
{
	if (sperator != x.sperator) 
		return false;
	int xsize = x.rule.rightSide.expression.size();
	if (xsize != rule.rightSide.expression.size())
		return false;
	if (!(x.lookahead == lookahead))
		return false;
	if (x.rule.leftSide != rule.leftSide)
		return false;
	for(IItem myitem: x.rule.rightSide)
		if (find(rule.rightSide.expression.begin(),rule.rightSide.expression.end(), myitem) != rule.rightSide.expression.end())
			return false;
	return true;
}


bool StateItem::operator < (const StateItem& x) const
{
	if (sperator < x.sperator) return true;
	if (sperator > x.sperator) return false;
	int xsize = x.rule.rightSide.expression.size();
	if (xsize > rule.rightSide.expression.size())
		return true;
	if (xsize < rule.rightSide.expression.size())
		return false;

	if (x.lookahead > lookahead)
		return true;
	if (x.lookahead < lookahead)
		return false;
	if (x.rule.leftSide < rule.leftSide)
		return false;
	if (x.rule.leftSide > rule.leftSide)
		return true;
	for (IItem item : rule.rightSide)
	{
		if (find(x.rule.rightSide.expression.begin(),
		         x.rule.rightSide.expression.end(), item) != x.rule.rightSide.expression.end())
			return true;
	}
	return false;
}
