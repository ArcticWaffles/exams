#include "stdafx.h"
#include "QuestionMC.h"

using namespace std;



QuestionMC::QuestionMC(string theQuestion, int pointValue, string theAnswer)
	:Question(theQuestion, pointValue), answer(theAnswer)
{}


QuestionMC::~QuestionMC()
{}

void QuestionMC::addOption(std::string option)
{
	options.push_back(option);
}

string QuestionMC::printOptions()
{
	string optionString = "";
	char optionLabel = 'A';
	for (int i = 0; i < options.size(); i++)
	{
		optionString.push_back(optionLabel + i);
		optionString += ": " + options[i] + "\n";
	}
	return optionString;
}

string QuestionMC::getAnswer()
{
	return answer;
}
