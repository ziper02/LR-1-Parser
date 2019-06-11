
#include  "LR_1.h"


LR1::LR1(vector<string> arg, string start)
{
	int i;
	bool flag = true;
	createStartRule(start);
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

void LR1::createStartRule(string st)
{
	string temp = st;
	st.insert(st.size() - 1, 1, '`');
	st.append(" : ");
	st.append(temp);
	this->start = Rule(st);
	rules.push_back(start);
}