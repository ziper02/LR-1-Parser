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
	for (StateItem state : x)
		if (state == *this)
			return true;
	return false;
}

/*
bool StateItem::existwo(vector<StateItem> x)
{
	for (StateItem state : x)
	{
		if (this->equalstwo(state))
			return true;
	}
	return false;
}


bool StateItem::equalstwo(StateItem state)
{
	if (this->sperator != state.sperator)
		return false;
	int xsize = state.rule.rightSide.expression.size();
	if (xsize != rule.rightSide.expression.size())
		return false;
	if (state.rule.leftSide != rule.leftSide)
		return false;
	for (int i = 0; i < state.rule.rightSide.expression.size(); i++)
		if (state.rule.rightSide.expression.at(i) != rule.rightSide.expression.at(i))
			return false;
	return true;
}
*/





bool StateItem::operator == (const StateItem& x) const
{
	if (sperator != x.sperator) 
		return false;
	int xsize = x.rule.rightSide.expression.size();
	if (xsize != rule.rightSide.expression.size())
		return false;
	if (x.lookahead != lookahead)
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



void StateItem::print()
{
	string st = rule.getRuleString();
	char ch = 250;
	int clacsp=0;
	for (int i=0;i<sperator;i++)
		clacsp += rule.rightSide.expression.at(i).name.size()+1;
	st.insert(rule.leftSide.short_name.size()+7+ clacsp, 1, ch);
	cout << st << "," << lookahead.name;
}




IItem StateItem::getnext()
{
	if ((sperator) == rule.rightSide.expression.size())
		return Terminal("");
	return rule.rightSide.expression.at(sperator);
}
