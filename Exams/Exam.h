#pragma once
#ifndef EXAM_H 
#define EXAM_H

#include <string>
#include <vector>
#include "Question.h"
#include "Student.h"

class Exam
{
public:
	Exam(std::string, std::vector<Question*>);
	~Exam();
	static std::vector<Question*> loadExamQuestions();
	double calculatePointsPossible();
	std::string getExamName();
	std::vector<Question*> getQuestionList();

private:
	std::string examName;
	std::vector<Question*> questionList;
};

#endif