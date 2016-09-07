#include "stdafx.h"
#include "Student.h"


Student::Student(std::string theFirstName, std::string theLastName)
	:firstName(theFirstName), lastName(theLastName)
{
}


Student::~Student()
{
}

std::string Student::getFirstName()
{
	return firstName;
}

std::string Student::getLastName()
{
	return lastName;
}
