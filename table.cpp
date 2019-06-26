#include "lr(1) parser/LR_1.h"

table::table(Automata automata)
{
	LR1 context = automata.context;
	this->automata = automata;
	int i = 0;
	isItLR1 = true;
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
					if(ACTION.count(tempterminal)==0)
						ACTION[tempterminal] = result;
					else
					{
						pair<char, int> resultexist;
						resultexist.first = ACTION[tempterminal].first;
						resultexist.second = ACTION[tempterminal].second;
						if(result.first!= resultexist.first || result.second != resultexist.second )
						{
							isItLR1 = false;
							return;
						}
					}
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
					if (ACTION.count(input) == 0)
						ACTION[input] = result;
					else
					{
						pair<char, int> resultexist;
						resultexist.first = ACTION[input].first;
						resultexist.second = ACTION[input].second;
						if (result.first != resultexist.first || result.second != resultexist.second)
						{
							isItLR1 = false;
							return;
						}
					}
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
							if (ACTION.count(input) == 0)
								ACTION[input] = result;
							else
							{
								pair<char, int> resultexist;
								resultexist.first = ACTION[input].first;
								resultexist.second = ACTION[input].second;
								if (result.first != resultexist.first || result.second != resultexist.second)
								{
									isItLR1 = false;
									return;
								}
							}
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
	if (isItLR1 == false)
	{
		cout << "We build Automate but we cant build table , this language is not L1\n";
		return;
	}
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


void table::parse(vector<string> str)
{
	vector<Terminal> Input;
	stack <pair<IItem, int>> Stack;
	pair<IItem, int> inputSTACK;
	pair<int, Terminal> inputACTION;
	pair<int, Variable> inputGOTO;
	Rule rule;
	bool flag=true;
	if(isItLR1==false)
	{
		cout << "Cant prasing exp because table is not exist.\n";
		return;
	}
	cout << "\n Start Prasing: ";
	for(string ch: str)
	{
		cout << ch;
		Input.push_back(Terminal(ch));
	}
	Input.push_back(Terminal("$"));
	inputSTACK.first = Terminal("$");
	inputSTACK.second = 0;
	Stack.push(inputSTACK);
	cout << "\n";
	while(flag)
	{
		flag = false;
		inputACTION.first = Stack.top().second;
		if (Input.size() != 0)
			inputACTION.second = Input.at(0);
		else
		{
			cout << "\nparsing failed\n";
			return;
		}

		
		if(ACTION[inputACTION].first=='s')
		{
			inputSTACK.first = Input.at(0);
			inputSTACK.second = ACTION[inputACTION].second;
			if(Input.size()==0)
			{
				cout << "\nparsing failed\n";
				return;
			}
			cout << "Shift " << inputACTION.second.name<<"\n";
			Input.erase(Input.begin());
			Stack.push(inputSTACK);
			flag = true;
		}
		else if (ACTION[inputACTION].first == 'r')
		{
			rule = automata.context.rules.at(ACTION[inputACTION].second);
			for (int i = 0; i < rule.rightSide.expression.size(); i++)
			{
				if(Stack.empty()==false)
					Stack.pop();
				else
				{
					cout << "\nparsing failed\n";
					return;
				}
			}
			cout << "Reduce " << rule.getRuleString() << "\n";
			inputSTACK.first = rule.leftSide;
			inputGOTO.first = Stack.top().second;
			inputGOTO.second = rule.leftSide;
			inputSTACK.second = GOTO[inputGOTO];
			Stack.push(inputSTACK);
			flag = true;
		}
		else if (ACTION[inputACTION].first == 'a')
		{
			cout << "\nparsing success\n";
			return;
		}

	}

	cout << "\nparsing failed\n";

}
