#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <numeric>
#include "ReadFile.cpp"
#include "Day2.cpp"
using namespace std;

bool  TestValues(list<int> L);
void TestMessage (string Message);
bool Testing = true;
int safeCount = 0;


int main()
{
	list<list<int>> DynamicArray;

	cout << "\n reading file\n--------";
	string fileInfo = readFile("Puzzles\\AdventDay2.txt");

	cout<< "\n parsing file\n---------";
	parseReports(fileInfo, DynamicArray);

	// Check every set of reports and report back safe (1) or unsafe (0). Keep count of safe reports
	//loop each report and test
	for_each
	(DynamicArray.begin(),DynamicArray.end(), [](const std::list<int> innerList)
	{
		// test the set of values
		bool isSafe = TestValues(innerList);
		TestMessage("\n is Safe: " + to_string(isSafe) + "\n");
		if (isSafe)
			safeCount++;
	});

	cout<< safeCount << " Safe reports\n---------";

	return 0;
}

void TestMessage (string Message)
{
	if (Testing == true)
		cout << Message;
}

// function for printing the elements in a list
bool  TestValues(list<int> L)
{
	//set variables
	int lastNum = -1;
	int CurrentNum=0;
	bool isIncreasing = false;
	bool isDecreasing = false;

	TestMessage("Testing Report: ");

	//loop the list
	for (int i:L)
	{
		CurrentNum = L.front();
		 TestMessage(to_string(CurrentNum) + " ");
		//if first number just set and go to next
		if(lastNum == -1)
		{
			lastNum = CurrentNum;
			L.pop_front();
			continue;
		}

		// check if numbers are the same
		if (CurrentNum == lastNum)
		{ TestMessage("\nfailed Same check\n"); return 0;}

		//Test if numbers are increasing or decreasing
		// if both false then hasent been checked yet
		if ( isIncreasing == false && isDecreasing == false)
		{
			if (CurrentNum > lastNum)
				{isIncreasing = true; TestMessage("^");}
			else
				{isDecreasing = true; TestMessage("V");}
		} else if (isIncreasing == true && CurrentNum < lastNum)
		{ TestMessage("\nfailed increasing check\n"); return 0;}
		else if (isDecreasing == true && CurrentNum > lastNum)
		{ TestMessage("\nFailed Decreasing check\n");return 0;}

		int difference = abs(lastNum - CurrentNum);
	
		//test if differnce in numbers are between 1 and 3
		if (difference < 0 || difference > 3)
			{
				TestMessage("\nFailed difference check " + to_string(difference) + "\n");
				return 0;
			}

		L.pop_front();
		lastNum = CurrentNum;
	}
	// end of for each

	//if past all tests then set to safe(1)
	return 1;
}