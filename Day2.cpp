// Functions used for day 2 of Advant of code 2024
#include <string>
#include <list>
#include <iostream>
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