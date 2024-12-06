#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include "ReadFile.cpp"
#include "parseCords.cpp"
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

int main()
{
	list<int> Cords1;
	list<int> Cords2;
	list<int> DifferenceList;
	list<int> SimilarityScore;
	int sum;

	cout << "\n reading file\n--------";
	string fileInfo = readFile();

	cout<< "\n parsing file\n---------";
	parseCords(fileInfo,Cords1,Cords2);

	cout<< "\n Sorting Lists\n---------";
	Cords1.sort();
	Cords2.sort();

	CreateDifferenceList(Cords1,Cords2,DifferenceList);

	sum = std::accumulate(DifferenceList.begin(), DifferenceList.end(), 0);
	cout << "\n Sum of Differece - Answer: "<<sum << "\n---------";

	cout<< "\n Getting similarity score\n---------------------";
	CalculateSimilarityScore (Cords1,Cords2,SimilarityScore);

	sum = std::accumulate(SimilarityScore.begin(), SimilarityScore.end(), 0);
	cout << "\n Sum of Similarity Score - Answer: "<<sum << "\n---------";
	
	return 0;
}