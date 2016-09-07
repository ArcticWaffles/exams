#pragma once

#ifndef QUESTIONMC_H 
#define QUESTIONMC_H

#include "Question.h"
#include <vector>

//Multiple choice question. Derived from Question class.
class QuestionMC :
	public Question
{
public:
	QuestionMC(std::string, int, std::string);
	~QuestionMC();
	void addOption(std::string option);
	std::string printOptions() override;
	std::string getAnswer() override;

private:
	std::string answer;
	std::vector<std::string> options;
};

#endif

