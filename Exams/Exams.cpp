
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "Question.h"
#include "QuestionMC.h"
#include "QuestionTF.h"
#include "Exam.h"
#include "ExamResults.h"


using namespace std;

//Presents the main menu and returns the user's selection
int getMenuChoice()
{
	cout << "\nMain Menu:" << endl;
	cout << "1 - Load an Exam" << endl;
	cout << "2 - Take an Exam" << endl;
	cout << "3 - Show Exam Results" << endl;
	cout << "4 - Quit" << endl;
	int menuSelection = 0;
	cin >> menuSelection;
	//Checks for invalid input. 
	while (cin.fail() || menuSelection < 1 || menuSelection > 4)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid entry. Please enter 1, 2, 3, or 4." << endl;
		cin >> menuSelection;
	}
	return menuSelection;
}

//Gives an exam
ExamResults administerExam(Student &student, Exam exam)
{
	cout << "\nWelcome, " << student.getFirstName() << endl;
	cout << "You selected: " << exam.getExamName() << endl;
	cout << "There will be " << exam.getQuestionList().size() << " questions." << endl;
	cout << "If the question is true/false, enter T or F." << endl;
	cout << "If it is multiple choice, enter the letter of the best answer." << endl;
	cout << "Good luck!" << endl;

	//New ExamResults object to keep track of points and missed questions
	ExamResults examResults(student, exam);
	double runningTotalPointsPossible = 0;

	//Loops through all questions in the exam
	for (size_t i = 0; i < exam.getQuestionList().size(); i++)
	{
		Question* question = exam.getQuestionList().at(i);
		string theAnswer = question->getAnswer();
		string studentAnswer = "";
		string result = "";
		cout << "\n" << question->formatQuestionForExam() << endl; //Prints the question
		getline(cin, studentAnswer);
		//Changes input to uppercase to make comparison case-insensitive
		transform(studentAnswer.begin(), studentAnswer.end(), studentAnswer.begin(), ::toupper);

		if (theAnswer == "TRUE")
		{
			result = (studentAnswer.compare("TRUE") == 0 || studentAnswer.compare("T") == 0) ? "Correct" : "Incorrect";
		}
		else if (theAnswer == "FALSE")
		{
			result = (studentAnswer.compare("FALSE") == 0 || studentAnswer.compare("F") == 0) ? "Correct" : "Incorrect";
		}
		else //Answer is multiple choice
		{
			result = (studentAnswer.compare(theAnswer) == 0) ? "Correct" : "Incorrect";
		}

		if (result == "Correct")
		{
			cout << "\nCorrect!" << endl;
			examResults.addPointsScored(question->getValue());
		}
		else
		{
			cout << "\nSorry, the correct answer is " << question->getAnswer() << endl;
			examResults.addMissedQuestions(question);
		}
		runningTotalPointsPossible += question->getValue();
		cout << "So far, you have earned " << examResults.getPointsScored() << " points out of " << runningTotalPointsPossible << endl;
	}
	cout << "\nEnd of exam." << endl;
	return examResults;
}


int main()
{
	//Stores exams loaded into the program
	vector<Exam> examCollection;
	//Stores results of each exam taken
	vector<ExamResults> takenExams;

	int menuSelection = getMenuChoice();
	//Loop presents main menu after each action until user selects "Quit"
	while (menuSelection != 4)
	{
		switch (menuSelection)
		{
			//Menu option "Load Exam"
		case 1:
		{
			vector<Question*> examQuestions;
			examQuestions = Exam::loadExamQuestions();
			string name = "";
			cout << "\nEnter a name for this exam:" << endl;
			getline(cin, name);
			Exam newExam(name, examQuestions); //Creates exam
			examCollection.push_back(newExam); //Adds exam to exams vector
			cout << "\nExam has been loaded." << endl;
			menuSelection = getMenuChoice();
			break;
		}
		//Menu option "Take an Exam"
		case 2:
			if (examCollection.empty())
			{
				cout << "\nThere are no exams available." << endl;
			}
			else
			{
				cout << "\nChoose an exam to take:" << endl;
				//Prints numbered list of all exams that have been loaded
				for (size_t i = 0; i < examCollection.size(); i++)
				{
					cout << i + 1 << "  " << examCollection[i].getExamName() << endl;
				}
				int examChoice = 0;
				cin >> examChoice;
				//Checks for invalid input
				while (cin.fail() || examChoice < 1 || examChoice > examCollection.size())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nInvalid entry. Please enter a number from the above list." << endl;
					cin >> examChoice;
				}
				//Student variables
				string firstName = "";
				string lastName = "";
				//Clear buffer of any previous input
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nPlease enter your first name:" << endl;
				getline(cin, firstName);
				cout << "\nPlease enter your last name:" << endl;
				getline(cin, lastName);
				//Create student
				Student student(firstName, lastName);
				//Give exam
				ExamResults currentExam = administerExam(student, examCollection[examChoice - 1]);
				//Store exam results
				takenExams.push_back(currentExam);
			}
			menuSelection = getMenuChoice();
			break;

			//Menu option "Show Exam Results"
		case 3:
			if (takenExams.empty())
			{
				cout << "\nThere are no exam results to display." << endl;
			}
			else
			{
				cout << "\nExam results for this session:" << endl;
				for (size_t i = 0; i < takenExams.size(); i++)
				{
					ExamResults currentExam = takenExams[i];
					cout << "\nName: " << currentExam.getStudent().getLastName() << ", " << currentExam.getStudent().getFirstName() << endl;
					cout << "Exam: " << currentExam.getExam().getExamName() << endl;
					cout << "Points Scored: " << currentExam.getPointsScored() << "/" << currentExam.getExam().calculatePointsPossible() << endl;
					double decimalScore = currentExam.getPointsScored() / currentExam.getExam().calculatePointsPossible();
					double percentageScore = decimalScore * 100;
					cout << setprecision(2) << fixed;
					cout << "Percentage Score: " << percentageScore << "%" << endl;
				}
			}
			menuSelection = getMenuChoice();
			break;
		}
	}

	//Menu option "Quit"
	cout << "\nThank you." << endl;
}


