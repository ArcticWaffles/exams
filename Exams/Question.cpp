#include "stdafx.h"
#include "Question.h"
#include <iostream>
#include <sstream>

using namespace std;

Question::Question(std::string theQuestion, int pointValue)
	: question(theQuestion), value(pointValue)
{}

Question::~Question()
{}

string Question::getQuestion()
{
	return question;
}

double Question::getValue()
{
	return value;
}

string Question::printOptions()
{
	return string();
}

string Question::getAnswer()
{
	return string();
}

string Question::formatQuestionForExam()
{
	stringstream s;
	s << "\nQuestion: " << question << "\nPoint Value: " << value << "\n" << printOptions();
	string output = s.str();
	return output;
}


