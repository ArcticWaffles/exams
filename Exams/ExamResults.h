#pragma once

#ifndef EXAMRESULTS_H 
#define EXAMRESULTS_H

#include "Student.h"
#include "Exam.h"

#include <string>

/*ExamResults stores the results of each exam that is taken. Every object refers to a particular
student and a particular exam. This allows the program to give multiple exams to multiple students
and store the information from each instance. */

class ExamResults
{
public:
	ExamResults(Student, Exam);
	~ExamResults();
	void addPointsScored(double);
	double getPointsScored();
	void addMissedQuestions(Question*);
	std::vector<Question*> getMissedQuestions();
	Exam getExam();
	Student getStudent();

private:
	double pointsScored;
	std::vector<Question*> missedQuestions;
	Exam exam;
	Student student;

};

#endif

