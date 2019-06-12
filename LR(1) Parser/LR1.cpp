
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
			rules.push_back(temp);
	}
		
}

void LR1::printGrammer()
{
	cout << "The Rules are :\n";
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


set<Terminal> LR1::First(vector<IItem> st)
{
	map <IItem, set<Terminal>> result = this->First();
	set<Variable> eps = this->eps();
	set<Terminal> first=result[st.at(0)];
	Variable* p;
	 if(p = dynamic_cast<Variable*>(&st.at(0)))
	{
		for (int i = 2; i < st.size() && eps.count(*p);)
		{
			first.insert(result[st.at(i)].begin(),result[st.at(i)].end());
			if ((p = dynamic_cast<Variable*>(&st.at(++i)))==NULL)
			{
				first.insert(result[st.at(i)].begin(), result[st.at(i)].end());
				break;
			}
		}
	}
	return first;
}


set<Variable> LR1::eps()
{
	set <Variable> que;
	for(Rule rule: rules)
	{
		if (rule.rightSide.expression.at(0) == Terminal("e"))
			que.insert(rule.leftSide);

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
					if(find(que.begin(), que.end(), (*q)) ==que.end())
						flag = false;
				}
				if(flag)
					if (find(que.begin(), que.end(), (rule.leftSide)) == que.end())
						que.insert(rule.leftSide);
			}
		}
	}
	return que;
}

map<IItem,set<Terminal>> LR1::First()
{
	map<IItem, set<Terminal>> result;
	set<Variable> eps = this->eps();
	bool flag=true;
	for(Rule rule: this->rules)
	{
		for(IItem item: rule.rightSide.expression)
		{
			if (Terminal * p = dynamic_cast<Terminal*>(&item))
				result[item] = { *p };
			else
				result[item] = {};
		}
		result[rule.leftSide] = {};
	}
	result[Terminal("$")] = { Terminal("$") };
	while(flag)
	{
		for (Rule rule : rules)
		{
			int sizeflag = result[rule.leftSide].size();
			result[rule.leftSide].insert(result[rule.rightSide.expression.at(0)].begin(),
				result[rule.rightSide.expression.at(0)].end());
			flag = (result[rule.leftSide].size() != sizeflag);

			for(int i=1;i<rule.rightSide.expression.size();i++)
			{
				sizeflag = result[rule.leftSide].size();
				if (find(eps.begin(), eps.end(), rule.rightSide.expression.at(i)) != eps.end())
				{
					result[rule.leftSide].insert(result[rule.rightSide.expression.at(i)].begin(),
						result[rule.rightSide.expression.at(i)].end());
				}
				else
					break;
				flag = flag || (sizeflag != result[rule.leftSide].size());
			}
		}
	}
	return result;
}






