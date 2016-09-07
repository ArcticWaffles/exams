#include "stdafx.h"
#include "ExamResults.h"


ExamResults::ExamResults(Student theStudent, Exam theExam)
	:student(theStudent), exam(theExam)
{
}


ExamResults::~ExamResults()
{
}


void ExamResults::addPointsScored(double points)
{
	pointsScored += points;
}


double ExamResults::getPointsScored()
{
	return pointsScored;
}


void ExamResults::addMissedQuestions(Question * missedQuestion)
{
	missedQuestions.push_back(missedQuestion);
}


std::vector<Question*> ExamResults::getMissedQuestions()
{
	return missedQuestions;
}

Exam ExamResults::getExam()
{
	return exam;
}

Student ExamResults::getStudent()
{
	return student;
}