
#include "LR_1.h"


Rule::Rule(string rule)
{
	int i = 0, startIndex;
	bool flag = true;
	string temp = "";
	while (flag)
	{
		temp.append(string(1, rule.at(i)));
		i++;
		if (rule.at(i) == '>')
			flag = false;
	}
	temp.append(string(1, rule.at(i)));
	leftSide = Variable(temp);
	i = i + 4;
	startIndex = i;
	for (i; i < rule.size(); i++)
	{
		if (rule.at(i) == '|')
		{
			temp = rule.substr(startIndex, i - startIndex - 1);
			startIndex = i + 1;
			rightSide.push_back(Item(temp));
		}
	}
	temp = rule.substr(startIndex, i - startIndex + 1);
	rightSide.push_back(Item(temp));
}


string Rule::getRuleString()
{
	string temp = "";
	int i = 0;
	for (Item item : rightSide)
	{
		temp.append(leftSide.name);
		temp.append(" --> ");
		temp.append(item.getItemString());
		if (i != rightSide.size() - 1)
			temp.append("\n");
		i++;
	}
	return temp;
}