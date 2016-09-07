#pragma once

#ifndef STUDENT_H 
#define STUDENT_H

#include <string>
#include <vector>
#include "Question.h"

class Student
{
public:
	Student(std::string, std::string);
	~Student();
	std::string getFirstName();
	std::string getLastName();

private:
	std::string firstName;
	std::string lastName;

};

#endif 
