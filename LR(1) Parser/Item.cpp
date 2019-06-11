
#include "LR_1.h"

Item::Item(string item)
{
	int i;
	bool flag = true;
	string temp = "";
	for (i = 0; i < item.size(); i++)
	{
		if (item.at(i) == '<')
		{
			temp = "";
			flag = true;
			while (flag)
			{
				temp.append(string(1, item.at(i)));
				i++;
				if (item.at(i) == '>')
					flag = false;
			}
			temp.append(string(1, item.at(i++)));
			expression.push_back(Variable(temp));
		}
		else if (item.at(i) != ' ')
		{
			temp = "";
			flag = true;
			while (flag)
			{
				temp.append(string(1, item.at(i)));
				i++;
				if (i == item.size())
					flag = false;
				else if (item.at(i) == ' ')
					flag = false;
			}
			expression.push_back(Terminal(temp));
		}
	}

}

string Item::getItemString()
{
	string temp = "";
	for (IItem minor : expression)
	{
		temp.append((&minor)->name);
		temp.append(string(1, ' '));
	}
	return temp;
}

Item::Item(Item& items)
{
	expression.push_back(Terminal("*"));
	for(IItem iitem: items.expression)
		expression.push_back(iitem);
}
