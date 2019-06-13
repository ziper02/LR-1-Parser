#include "lr(1) parser/LR_1.h"

StateItem::StateItem(Rule rule, Terminal terminal,LR1 context)
{
	this->rule = rule;
	this->lookahead = terminal;
	this->context = context;
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
	return find(x.begin(), x.end(), *this) != x.end();
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
	for(int i=0;i<x.rule.rightSide.expression.size();i++)
		if (x.rule.rightSide.expression.at(i)!=rule.rightSide.expression.at(i))
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
	for (int i = 0; i < x.rule.rightSide.expression.size(); i++)
		if (x.rule.rightSide.expression.at(i).isExist(rule.rightSide.expression))
			return false;
	return false;
}





IItem StateItem::getnext()
{
	if ((sperator) == rule.rightSide.expression.size())
		return Terminal("");
	return rule.rightSide.expression.at(sperator);
}
