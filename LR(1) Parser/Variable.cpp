
#include "LR_1.h"
using namespace std;

Variable::Variable(string originalName)
{
	name = "";
	this->name = originalName; //thrsid
	string temp;
	for (int i = 0; i < originalName.size(); i++)
	{
		if (originalName[i] != '<' && originalName[i] != '>')
		{
			temp.push_back(originalName.at(i));
			short_name.append(temp);
		}
	}
};