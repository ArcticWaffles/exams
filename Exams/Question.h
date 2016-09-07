#pragma once

#ifndef QUESTION_H 
#define QUESTION_H
#include <string>

//Base class for specific question types
class Question
{
public:
	Question(std::string, int);
	std::string getQuestion();
	double getValue();
	virtual std::string printOptions();
	virtual std::string getAnswer();
	virtual ~Question();
	std::string formatQuestionForExam();

protected:
	std::string question;
	double value;


};

#endif 

