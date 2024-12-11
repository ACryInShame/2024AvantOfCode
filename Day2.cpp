// Functions used for day 2 of Advant of code 2024
#pragma once
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "ReadFile.cpp"
#include "TestMessage.cpp"
using namespace std;

void StringToInts (list<int> IntList);
void showlist(list<int> L);

void parseReports (string input, list<list<int>>& DynamicArray)
{
   string holdString; //holds current string;
   int Posision; // Holds current posision in string
   int SubPosision; // Holds current posision in string in nested loop

   // run through each line in input and pull it into DynamicArray
   for (int i=0;input.size()>1;i++)
   {
      //find the new line
      Posision = input.find('\n');
      holdString = input.substr(0,Posision);

      //create new list
      list<int> newListRef;

      // add numbers into a list
      for (int i=0;holdString.size()>=1;i++)
      {
         // find number
         SubPosision = holdString.find(' ');
         // add to temp list
         newListRef.push_back(stoi(holdString));

         // check if end of string
         if (SubPosision == -1) // This ends the loop if we've gotten to the end of the string
            break;

         //if not end, remove current line
         holdString = holdString.substr(SubPosision+1);
      };
      //add list into DynamicArray
      DynamicArray.push_back(newListRef);

      //remove finished line from the string by subsringing just past the new line (+1)
      input = input.substr(Posision+1);
   };
}

// function for printing the elements in a list
bool  TestValues(list<int> L,bool IsDampenerOn)
{
	//set variables
	int lastNum = -1;
	int CurrentNum = 0;
	bool DampenerTriggered = false;
	bool isIncreasing = false;
	bool isDecreasing = false;

	auto iterator = L.begin();

	TestMessage("Testing Report: ");

	//loop the list
	for (int i:L)
	{
		//update current number
		CurrentNum = *iterator;
		TestMessage(to_string(CurrentNum) + " ");

		//if first number, set and go to next
		if(lastNum == -1)
		{
			lastNum = CurrentNum;
			++iterator;
			continue;
		}

		// check if numbers are the same
		// If dampening is on, test if it's been triggered, if not skip to next number
		// do not update "Last numeber" as the current number is going to be ignored.
		if (CurrentNum == lastNum)
			if (IsDampenerOn && !DampenerTriggered)
				{
					DampenerTriggered = true;
					TestMessage("X ");
					++iterator;
					continue;
				}
			else
			{ TestMessage("\nfailed Same check\n"); return 0;}

		int difference = abs(lastNum - CurrentNum);
	
		//test if differnce in numbers are between 1 and 3
		// If dampening is on, test if it's been triggered, if not skip to next number
		// do not update "Last numeber" as the current number is going to be ignored.
		if (difference < 0 || difference > 3)
			if (IsDampenerOn && !DampenerTriggered)
				{
					DampenerTriggered = true;
					TestMessage("X ");
					++iterator;
					continue;
				}
			else
			{
				TestMessage("\nFailed difference check " + to_string(difference) + "\n");
				return 0;
			}

		//Test if numbers are increasing or decreasing
		// if both false then hasent been checked yet
		// If dampening is on, test if it's been triggered, if not skip to next number
		// do not update "Last numeber" as the current number is going to be ignored.
		// if 
		if ( isIncreasing == false && isDecreasing == false)
		{
			if (CurrentNum > lastNum)
				{isIncreasing = true; TestMessage("^ ");}
			else
				{isDecreasing = true; TestMessage("V ");}
		} 
		else 
			if (isIncreasing == true && CurrentNum < lastNum)
				if (IsDampenerOn && !DampenerTriggered)
				{
					DampenerTriggered = true;
					TestMessage("X ");
					++iterator;
					continue;
				}
				else
				{ TestMessage("\nfailed increasing check\n"); return 0;}
			else 
				if (isDecreasing == true && CurrentNum > lastNum)
					if (IsDampenerOn && !DampenerTriggered)
					{
						DampenerTriggered = true;
						TestMessage("X ");
						++iterator;
						continue;
					}
				else
				{ TestMessage("\nFailed Decreasing check\n");return 0;}

		++iterator;
		lastNum = CurrentNum;
	}
	// end of for each

	//if past all tests then set to safe(1)
	return 1;
}

//--------------------------------------------------------------------------
//----------------------------Main process----------------------------------
//--------------------------------------------------------------------------
int safeCount = 0;
string FileName = "Puzzles\\AdventDay2.txt";

void Day2Part1 ()
{
   list<list<int>> DynamicArray;

	cout << "reading file\n--------\n";
	string fileInfo = readFile(FileName);

	cout<< "parsing file\n---------\n";
	parseReports(fileInfo, DynamicArray);

	// Check every set of reports and report back safe (1) or unsafe (0). 
	// Keep count of safe reports
	//loop each report and test
	for_each
	(DynamicArray.begin(),DynamicArray.end(), [](const std::list<int> innerList)
	{
		// test the set of values
		bool isSafe = TestValues(innerList,false);
		TestMessage("\n is Safe: " + to_string(isSafe) + "\n");
		if (isSafe)
			safeCount++;
	});

	cout<< "Safe reports: "<< safeCount <<"\n---------\n";
}

void Day2Part2 ()
{
	list<list<int>> DynamicArray;

	cout << "reading file\n--------\n";
	string fileInfo = readFile(FileName);

	cout<< "parsing file\n---------\n";
	parseReports(fileInfo, DynamicArray);

	// Check every set of reports and report back safe (1) or unsafe (0). 
	// Keep count of safe reports
	//loop each report and test
	for_each
	(DynamicArray.begin(),DynamicArray.end(), [](const std::list<int> innerList)
	{
		// test the set of values
		bool isSafe = TestValues(innerList,true);
		TestMessage("\n is Safe: " + to_string(isSafe) + "\n");
		if (isSafe)
			safeCount++;
	});

	cout<< "Safe reports: "<< safeCount <<"\n---------\n";
}