// Functions used for day 1 of Advant of code 2024
#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include "ReadFile.cpp"
#include <numeric>
using namespace std;


// function for printing the elements in a list
void showlist(list<int> L)
{
	list<int>::iterator it;
	std::for_each (L.begin(),L.end(),[](int num)
	{
	cout << num << " ";
	});
}

void CreateDifferenceList(list<int> L1,list<int> L2,list<int>& L3)
{
	int count = L1.size(); // get size of list

	// pull the absolute value, of the difference of list 1 and list 2 and store it in list 3
	for (size_t i = 0; i < count; i++)
	{
	L3.push_front(abs(L1.front() - L2.front()));
	L1.pop_front();
	L2.pop_front();
	}
}

void parseCords (string input, list<int>& list1, list<int>& list2)
{
   string holdString; //holds current string;
   string tempInput = input;
   int tempInt; // Holds current number

   // run through each line in input and pull the two numbers out
   // put numbers into the 2 lists given in order
   for (int i=0;tempInput.size()>1;i++)
   {
      //find the first space and use it to fine the first number
      tempInt = tempInput.find(' ');
      holdString = tempInput.substr(0,tempInt);

      // put first number into the list
      list1.push_back(stoi(holdString));

      //remove the found number from the string by subsring just past it (+1)
      tempInput = tempInput.substr(tempInt+1);

      //find the second space and use it to fine the second number
      tempInt = tempInput.find('\n');
      holdString = tempInput.substr(0,tempInt);

      // put second number into the list
      list2.push_back(stoi(holdString));

      //remove the found number from the string by subsring just past it (+1)
      tempInput = tempInput.substr(tempInt+1);
   };
}

void CalculateSimilarityScore(list<int> L1,list<int> L2,list<int>& L3)
{
	list<int>::iterator it1= L1.begin();
	int count1 = L1.size();
	for (size_t i1 = 0; i1 < count1; i1++)
	{
		int score=0; // holds score while counting

		// nested for loop to compare values from list 1 to list 2
		list<int>::iterator it2= L2.begin();
		int count2 = L2.size();
		for (size_t i2 = 0; i2 < count2; i2++)
		{
			// if the two match, add the value of the number to the sililarity score
			if(*it1 == *it2)
				score += *it1;
			it2++;
		}
		it1++;
		L3.push_back(score);
	}
}

//--------------------------------------------------------------------------
//----------------------------Main process----------------------------------
//--------------------------------------------------------------------------

void Day1Part1 ()
{
   list<int> Cords1;
	list<int> Cords2;
	list<int> DifferenceList;
	int sum;

	cout << "Reading file\n--------\n";
	string fileInfo = readFile("Puzzles\\AdventDay1.txt");

	cout<< "Parsing file\n---------\n";
	parseCords(fileInfo,Cords1,Cords2);

	cout<< "Sorting Lists\n---------\n";
	Cords1.sort();
	Cords2.sort();

	CreateDifferenceList(Cords1,Cords2,DifferenceList);

	sum = std::accumulate(DifferenceList.begin(), DifferenceList.end(), 0);
	cout << "Sum of Differece - Answer: "<<sum << "\n---------\n";
}


void Day1Part2 ()
{
	list<int> Cords1;
	list<int> Cords2;
	list<int> SimilarityScore;
	int sum;

	cout << "Reading file\n--------\n";
	string fileInfo = readFile("Puzzles\\AdventDay1.txt");

	cout<< "Parsing file\n---------\n";
	parseCords(fileInfo,Cords1,Cords2);

	cout<< "Sorting Lists\n---------\n";
	Cords1.sort();
	Cords2.sort();

	cout<< "Getting similarity score\n---------------------\n";
	CalculateSimilarityScore (Cords1,Cords2,SimilarityScore);

	sum = std::accumulate(SimilarityScore.begin(), SimilarityScore.end(), 0);
	cout << "Sum of Similarity Score - Answer: "<<sum << "\n---------\n";
}