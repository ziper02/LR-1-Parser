#include "lr(1) parser/LR_1.h"



Automata::Automata(LR1 context)
{
	this->context = context;
	start.rules.push_back(StateItem(Rule(this->context.start),Terminal("$")));
	start.clousre(this->context);
	stats.push_back(start);
	
}


