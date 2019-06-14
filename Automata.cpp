#include "lr(1) parser/LR_1.h"



Automata::Automata(LR1 context)
{
	this->context = context;
	start.rules.push_back(StateItem(Rule(this->context.start),Terminal("$"),context));
	start.clousre(this->context);
 	stats.push_back(start);
	start.index=0;
	int flagsize = 0;
	
	while(flagsize != stats.size())
	{
		int i = flagsize;
		flagsize = stats.size();

		for(;i<flagsize;i++)
		{
			State state = this->stats.at(i);
			for (StateItem state_item : state.rules)
			{
				bool flagclear = false;
				State st{};
				for (StateItem state_item2 : state.rules)
				{
					if (state_item2.sperator != state_item2.rule.rightSide.expression.size())
					{
						flagclear = true;	
					}
				}
				if(flagclear)
				{
					for (StateItem state_item2 : state.rules)
					{
						if (state_item.getnext() == state_item2.getnext() && state_item2.exist(st.rules) == false)
						{
							st.rules.push_back(StateItem(state_item2.rule, state_item2.lookahead, context));
							st.rules.at(st.rules.size() - 1).sperator = state_item2.sperator;
						}
							
					}
					IItem temp = st.rules.at(0).getnext();

					st.delta();
					if (!st.rules.empty())
					{
						pair<State, IItem> input;
						input.first = state;
						input.second = temp;
						if (!this->stateExist(st))
						{
							st.index = stats.size();
							stats.push_back(st);
						}
							
						if (getState.count(input) == 0)
							getState[input] = st;
					}
				}	
			}
		}
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


void Automata::printAutomata()
{
	cout << "\n Automata:\n\n";
	int i = 0;
	for(State state: stats)
	{
		cout << "Stage number " << i <<"\n";
		for(StateItem state_item: state.rules)
		{
			state_item.print();
			cout << "\n";
		}
		i++;
		cout << "\n";
	}
	i = 0;
	for (State state : stats)
	{
		cout << i << " : ";
		vector<pair<int, IItem>> test;
		for (StateItem state_item : state.rules)
		{
			IItem temp=state_item.getnext();
			pair<State, IItem> input;
			input.first = state;
			input.second = temp;
			if (getState.count(input) != 0)
			{
				int j = 0;
				for (State state2 : stats)
				{
					if (getState[input] == state2)
						break;
					j++;
				}
				pair<int, IItem> input2;
				input2.first = j;
				input2.second = temp;
				if(find(test.begin(),test.end(),input2)==test.end())
				{
					cout << "[ " << j << " , " << temp.name << " ]";
					test.push_back(input2);
				}	
			}
		}
		i++;
		cout << "\n";
	}
}