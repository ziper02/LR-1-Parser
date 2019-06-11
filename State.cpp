#include "lr(1) parser/LR_1.h"



void State::clousre(LR1 context)
{
	bool flag = true;
	while (flag)
	{
		flag = false;
		int size = rules.size();
		for (StateItem state_item : rules)
		{
			if (!(state_item.rule.rightSide.expression.at(state_item.sperator)).isTerminal())
			{
				for (Rule rule : context.rules)
				{
					if (rule.leftSide == state_item.rule.rightSide.expression.at(state_item.sperator))
					{
						vector<IItem> forfirst = state_item.getBeta();
						forfirst.push_back(state_item.lookahead);
						for (Terminal terminal : context.First(forfirst))
						{
							StateItem state(rule, terminal);
							rules.insert(state);
						}
					}
				}
			}
		}
		if (size != rules.size())
			flag = true;
	}
}
