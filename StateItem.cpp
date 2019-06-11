

#include "lr(1) parser/LR_1.h"

StateItem::StateItem(Rule rule, Terminal terminal)
{
	this->rule = rule;
	this->lookahead = terminal;
	sperator = 0;
}



