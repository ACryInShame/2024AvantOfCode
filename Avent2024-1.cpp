#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <numeric>
#include "ReadFile.cpp"
#include "Day2.cpp"
using namespace std;

void showlist(list<int> L);

int main()
{
	list<int> Reports;

	cout << "\n reading file\n--------";
	string fileInfo = readFile("Puzzles\\AdventDay2.txt");

	cout << fileInfo;

	cout<< "\n parsing file\n---------";
	parseReports(fileInfo,Reports);

	showlist(Reports);

	/*

	CreateDifferenceList(Cords1,Cords2,DifferenceList);

	sum = std::accumulate(DifferenceList.begin(), DifferenceList.end(), 0);
	cout << "\n Sum of Differece - Answer: "<<sum << "\n---------";

	cout<< "\n Getting similarity score\n---------------------";
	CalculateSimilarityScore (Cords1,Cords2,SimilarityScore);

	sum = std::accumulate(SimilarityScore.begin(), SimilarityScore.end(), 0);
	cout << "\n Sum of Similarity Score - Answer: "<<sum << "\n---------";
	*/
	return 0;
}


// function for printing the elements in a list
void showlist(list<int> L)
{
	list<int>::iterator it;
	std::for_each (L.begin(),L.end(),[](int num)
	{
	cout << num << " " << endl;
	});
}