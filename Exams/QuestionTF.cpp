#include "stdafx.h"
#include "QuestionTF.h"

using namespace std;


QuestionTF::QuestionTF(string theQuestion, int pointValue, string theAnswer)
	:Question(theQuestion, pointValue), answer(theAnswer)
{}

QuestionTF::~QuestionTF()
{}

string QuestionTF::printOptions()
{
	return "(true/false)";
}

string QuestionTF::getAnswer()
{
	return answer;
}


