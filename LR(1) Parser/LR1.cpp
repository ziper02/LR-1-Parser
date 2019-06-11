
#include  "LR_1.h"

#include <algorithm>

LR1::LR1(vector<string> arg, string start)
{
	int i;
	bool flag = true;
	createStartRule(start);
	for (string st : arg)
	{
		vector < Rule > result= Rule::createRule(st);
		for(Rule temp: result)
		{
			rules.push_back(temp);
		}
	}
		

}

void LR1::printGrammer()
{
	cout << "The Rules are :";
	string temp = "";
	for (Rule rule : rules)
	{
		temp.append(rule.getRuleString());
		temp.append("\n");
	}
	cout << temp;
}

void LR1::createStartRule(string st)
{
	string temp = st;
	st.insert(st.size() - 1, 1, '`');
	st.append(" : ");
	st.append(temp);
	this->start = (Rule::createRule(st)).at(0);
	rules.push_back(start);
}


vector<Terminal> LR1::First(vector<IItem> st)
{
	vector<Terminal> vec;
	if (Terminal * p = dynamic_cast<Terminal*>(&st.at(0)))
	{
		vec.push_back(*p);
		return vec;
	}
	else
	{
		Variable* q = dynamic_cast<Variable*>(&st.at(0));
		for (Rule rule : rules)
		{
			if ((*q) == rule.leftSide)
			{
				vector<Terminal> temp;
				temp=First(rule.rightSide.expression);

			}
		}
	}
}


vector<Variable> LR1::eps()
{
	vector <Variable> que;
	for(Rule rule: rules)
	{
		if (rule.rightSide.expression.at(0) == Terminal("e"))
			que.push_back(rule.leftSide);

	}
	int sizeofque=0;

	while(que.size()!= sizeofque)
	{
		sizeofque = que.size();

		for(Rule rule:rules)
		{
			if(rule.includeTerminal()==false)
			{
				bool flag = true;
				for(IItem item: rule.rightSide.expression)
				{
					Variable* q = dynamic_cast<Variable*>(&item);
					if(find(que.begin(),que.size(),(*q))==que.end())
					{
						
					}
				}
			}
		}

	}




}