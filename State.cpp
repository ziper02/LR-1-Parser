#include "lr(1) parser/LR_1.h"



void State::clousre(LR1 context)
{
	bool flag = true;
	while (flag)
	{
		flag = false;
		int size = rules.size();
		for (int i=0;i<size;i++)
		{
			StateItem state_item = rules.at(i);
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
							StateItem state(rule, terminal,context);
							if (state.exist(this->rules) == false)
								rules.push_back(state);
						}
					}
				}
			}
		}
		if (size != rules.size())
			flag = true;
	}
}



void State::delta()
{
	for(StateItem rule : rules)
	{
		if ((rule.sperator + 1) != rule.rule.rightSide.expression.size())
			rule.sperator++;
	}
	this->clousre(rules.at(0).context);
}

bool State::operator==(const State& x) const
{
	if (this->rules.size() != x.rules.size())
		return false;
	for(StateItem rule : this->rules)
	{
		if (!rule.exist(x.rules))
			return false;
	}
	return true;
}