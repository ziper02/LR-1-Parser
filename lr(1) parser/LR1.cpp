
#include  "LR_1.h"


LR1::LR1(vector<string> arg, string start)
{
	int i;
	bool flag = true; 
	this->start = Variable(start);
	for (string st : arg)
		rules.push_back(Rule(st));

}

void LR1::printGrammer()
{
	string temp = "";
	for (Rule rule : rules)
	{
		temp.append(rule.getRuleString());
		temp.append("\n");
	}
	cout << temp;
}