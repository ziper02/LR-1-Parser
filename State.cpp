#include "lr(1) parser/LR_1.h"



void State::clousre(LR1 context)
{
	for(StateItem state_item: rules)
	{
		IItem temp = state_item.rule.rightSide.expression.at(state_item.sperator + 1);
		if (Variable * p = dynamic_cast<Variable*>(&temp))
		{
			for(Rule rule: context.rules)
			{
				if((*p)==rule.leftSide)
				{
					
				}
			}
		}
		else
		{
			// obj is not a C
		}
	}
}
