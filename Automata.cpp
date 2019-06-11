#include "lr(1) parser/LR_1.h"



Automata::Automata(LR1 context)
{
	this->context = context;
	start.rules.insert(StateItem(Rule(this->context.start),Terminal("$")));
	stats.push_back(start);
	start.clousre(this->context);
}


