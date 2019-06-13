#include "lr(1) parser/LR_1.h"



Automata::Automata(LR1 context)
{
	this->context = context;
	start.rules.push_back(StateItem(Rule(this->context.start),Terminal("$"),context));
	start.clousre(this->context);
	stats.push_back(start);
	int flagsize = 0;
	
	while(flagsize != stats.size())
	{
		for(State state: stats)
		{
			for(StateItem state_item : state.rules )
			{
				State st{};
				st.rules.push_back(StateItem(state_item.rule, state_item.lookahead, context));
				for (StateItem state_item2 : state.rules)
				{
					if (state_item.getnext() == state_item2.getnext() && state_item2.exist(st.rules)==false)
						st.rules.push_back(StateItem(state_item2.rule, state_item2.lookahead, context));
				}
				IItem temp= st.rules.at(0).getnext();
				st.delta();
				pair<State, IItem> input;
				input.first = st;
				input.second = temp;
				if(!this->stateExist(st))
					stats.push_back(st);
				if(getState.count(input)==0)
					getState[input] = st;
			}
		}
		flagsize = stats.size();
	}
}


bool Automata::stateExist(State st)
{
	for(State state : stats)
	{
		if (st == state)
			return true;
	}
	return false;
}

