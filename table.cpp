#include "lr(1) parser/LR_1.h"

table::table(Automata automata)
{
	LR1 context = automata.context;
	this->automata = automata;
	int i = 0;
	for(Rule rule : context.rules)
	{
		for(IItem item: rule.rightSide.expression)
		{
			if (item.isTerminalFixed())
				terminals.insert(Terminal(item.name));
			else
				variables.insert(Variable(item.name));	
		}
		if(i)
			variables.insert(rule.leftSide);
		i++;
	}
	terminals.insert(Terminal("$"));
	i = 0;
	for (State state : automata.stats)
	{
		for (StateItem state_item : state.rules)
		{
			IItem temp = state_item.getnext();
			pair<State, IItem> input;
			input.first = state;
			input.second = temp;
			if (automata.getState.count(input) != 0)
			{
				int j = 0;
				for (State state2 : automata.stats)
				{
					if (automata.getState[input] == state2)
						break;
					j++;
				}
				if (temp.isTerminalFixed())
				{
					pair<int, Terminal> tempterminal;
					tempterminal.first = i;
					tempterminal.second = Terminal(temp.name);
					pair<char, int> result;
					result.first = 's';
					result.second = j;
					ACTION[tempterminal] = result;
				}
				else
				{
					pair<int, Variable> tempvar;
					tempvar.first = i;
					tempvar.second = Variable(temp.name);
					GOTO[tempvar] = j;
				}
			}
			for (StateItem state_item : state.rules)
			{
				if(state_item.rule==context.start && state_item.sperator==1 && state_item.lookahead.name=="$")
				{
					pair<int, Terminal> input;
					input.first = i;
					input.second = state_item.lookahead;
					pair<char, int> result;
					result.first = 'a';
					result.second = -1;
					ACTION[input] = result;
				}
				else if (state_item.rule.rightSide.expression.size() == state_item.sperator)
				{
					int k = 0;
					for (Rule rule : context.rules)
					{
						if (rule == state_item.rule)
						{
							pair<int, Terminal> input;
							input.first = i;
							input.second = state_item.lookahead;
							pair<char, int> result;
							result.first = 'r';
							result.second = k;
							ACTION[input] = result;
						}
						k++;
					}
				}
			}
		}
		i++;
	}
}

void table::print()
{
	cout << "\nACTION Table : \n\n";
	int i = 0;
	for(Terminal terminal: terminals)
	{
		cout <<"	"<< terminal.name;
	}
	cout << "\n";
	for(State state: automata.stats)
	{
		cout << i << "	";
		for (Terminal terminal : terminals)
		{
			pair<int, Terminal> input;
			input.first = i;
			input.second = terminal;
			if(ACTION.count(input)==0)
				cout << "0	";
			else
			{
				pair<char, int> result = ACTION[input];
				if (result.second != -1)
					cout << result.first << "[" << result.second << "]	";
				else
					cout << "acc	";
			}
		}
		i++;
		cout << "\n";
	}

	cout << "\GOTO Table : \n\n";
	i = 0;
	for (Variable var: variables)
	{
		cout << "	" << var.name;
	}
	cout << "\n";
	for (State state : automata.stats)
	{
		cout << i << "	";
		for (Variable var : variables)
		{
			pair<int, Variable> input;
			input.first = i;
			input.second = var;
			if (GOTO.count(input) == 0)
				cout << "0	";
			else
			{
				cout << GOTO[input] << "	";
			}
		}
		i++;
		cout << "\n";
	}
}
