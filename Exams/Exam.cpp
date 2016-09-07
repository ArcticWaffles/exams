#include "stdafx.h"
#include "Exam.h"
#include "QuestionTF.h"
#include "QuestionMC.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>


using namespace std;

Exam::Exam(string name, vector<Question*> theQuestionList)
	:examName(name), questionList(theQuestionList)
{
}

Exam::~Exam()
{
}

//Loads an exam by prompting user for the filename and loading data into a vector. Vector consists of
//pointers so that questions of different types (classes) can be entered.
vector<Question*> Exam::loadExamQuestions()
{
	ifstream inQuestionFile; //Creates input file stream
	do
	{
		cout << "\nPlease enter the filename. Example: test.txt" << endl;
		string fileName = "";
		cin >> fileName;
		inQuestionFile.open(fileName);
		if (!inQuestionFile) //Checks that file can be opened
		{
			cout << "\nFile could not be opened. Make sure filename is correct and your file is in the program folder." << endl;
		}
	} while (!inQuestionFile);

	inQuestionFile.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	try
	{
		vector<Question*> questions;

		//Gets number of questions to be entered
		string line;
		getline(inQuestionFile, line);
		const int quantity = stoi(line); //Converts string to int

		for (int i = 0; i < quantity; i++) //Loops through given number of questions 
		{
			string questionType;
			string questionString;
			double pointValue;

			//Gets question type, point value, and question
			//Space delimited because question type and point value are on the same line
			getline(inQuestionFile, questionType, ' '); 
			getline(inQuestionFile, line);
			pointValue = stod(line); //Converts string to double
			getline(inQuestionFile, questionString);

			if (questionType.compare("TF") == 0) //Question is true/false
			{
				string tfAnswer;
				getline(inQuestionFile, tfAnswer);
				//Changes string to uppercase to make comparison case-insensitive
				transform(tfAnswer.begin(), tfAnswer.end(), tfAnswer.begin(), ::toupper); 
				if (tfAnswer.compare("TRUE") != 0 && tfAnswer.compare("FALSE") != 0)
				{
					throw invalid_argument("\nReceived an invalid true/false answer");
				}
				//Creates new question
				QuestionTF* newTFQuestion = new QuestionTF(questionString, pointValue, tfAnswer); 
				//Adds question to the questions vector
				questions.push_back(newTFQuestion); 

			}
			else //Question is multiple choice
			{
				//Gets number of answer choices
				int numberOfChoices;
				getline(inQuestionFile, line);
				numberOfChoices = stoi(line);
				//Vector temporarily holds choices until the question is ready to be created
				vector<string> choices; 
				for (int i = 0; i < numberOfChoices; i++)
				{
					getline(inQuestionFile, line);
					choices.push_back(line);
				}

				//Gets answer
				string answer;
				//Maximum char value is used to ensure the answer doesn't exceed the number of options
				char max = 'A' + (numberOfChoices - 1);
				getline(inQuestionFile, answer);
				//Converts all answers to uppercase for consistency
				answer.at(0) = toupper(answer.at(0));
				//Checks for invalid answer
				if (answer.at(0) < 'A' || answer.at(0) > max)
				{
					throw invalid_argument("\nReceived an invalid multiple choice answer.");
				}
				//Creates new question
				QuestionMC* newMCQuestion = new QuestionMC(questionString, pointValue, answer);
				for (int i = 0; i < numberOfChoices; i++)
				{
					(*newMCQuestion).addOption(choices[i]); //Adds answer choices to the new question
				}
				questions.push_back((newMCQuestion)); //Adds question to the questions vector
			}
		}
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clears input buffer
		inQuestionFile.close(); //Closes file
		return questions;
	}
	catch (ifstream::failure& e)
	{
		cerr << "\nError: Problem with reading file " << endl;
		exit(EXIT_FAILURE);
	}
	catch (const std::invalid_argument& e) 
	{
		cout << e.what() << " Please correct the file and try again." << endl;
		exit(EXIT_FAILURE);
	}

}

//Returns total points possible on an exam by adding up the point value of its questions
double Exam::calculatePointsPossible()
{
	double questionPointsSum = 0;
	for (size_t i = 0; i < questionList.size(); i++)
	{
		questionPointsSum += questionList[i]->getValue();
	}
	return questionPointsSum;
}

std::string Exam::getExamName()
{
	return examName;
}

std::vector<Question*> Exam::getQuestionList()
{
	return questionList;
}




