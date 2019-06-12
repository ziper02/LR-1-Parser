

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




bool StateItem::operator < (const StateItem& x) const
{
	if (sperator < x.sperator) return true;
	if (sperator > x.sperator) return false;
	else
	{
	
		if (rule.leftSide < x.rule.leftSide)
			return true;
		if (!(rule.leftSide < x.rule.leftSide))
			return false;
		for(int i=0;i<rule.rightSide.expression.size();i++)
		{
			if (i > x.rule.rightSide.expression.size())
				return true;
			if (rule.rightSide.expression.at(i) < x.rule.rightSide.expression.at(i))
				return true;
			if (!(rule.rightSide.expression.at(i) < x.rule.rightSide.expression.at(i)))
				return false;
		}
		for (int i = 0; i < x.rule.rightSide.expression.size(); i++)
		{
			if (i > rule.rightSide.expression.size())
				return false;
			if (rule.rightSide.expression.at(i) < x.rule.rightSide.expression.at(i))
				return true;
			if (!(rule.rightSide.expression.at(i) < x.rule.rightSide.expression.at(i)))
				return false;
		}
	}
}



