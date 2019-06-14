
#include "lr(1) parser/LR_1.h"

bool IItem::isTerminal()
{
	if (Terminal * p = dynamic_cast<Terminal*>(this))
		return true;
	else
		return false;
}


bool IItem::isTerminalFixed()
{
	if (name.at(0) == '<')
		return false;
	return true;
}

bool IItem::isExist(vector<IItem> vec) const
{
	for(IItem check : vec)
	{
		if (check == (*this))
			return true;
	}
	return false;
}

bool IItem::isExist(vector<IItem> vec) 
{
	for (IItem check : vec)
	{
		if (check == (*this))
			return true;
	}
	return false;
}

bool IItem::operator < (const IItem& x) const {
	if (name < x.name) return true;
	if (name >= x.name) return false;
}

bool IItem::operator > (const IItem& x) const 
{
	if (name > x.name) return true;
	if (name <= x.name) return false;
}

