#pragma once

#ifndef QUESTIONTF_H 
#define QUESTIONTF_H

#include "Question.h"

//True/false question. Derived from Question class.

class QuestionTF :
	public Question
{
public:
	QuestionTF(std::string, int, std::string);
	virtual ~QuestionTF();
	std::string printOptions() override;
	std::string getAnswer() override;

private:
	std::string answer;
};

#endif 

