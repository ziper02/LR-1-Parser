

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



