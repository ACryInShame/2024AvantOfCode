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

int main()
{
	list<int> Cords1;
	list<int> Cords2;
	list<int> DifferenceList;
	int sum;

	cout << "\nreading file\n--------";
	string fileInfo = readFile();

	cout<< "\nparsing file\n---------";
	parseCords(fileInfo,Cords1,Cords2);

	cout<< "\nSorting Lists\n---------";
	Cords1.sort();
	Cords2.sort();

	cout<< "\nChecking Lists\n---------";
	cout<< "\nList1\n";
	showlist(Cords1);
	cout<< "\nList2\n";
	showlist(Cords2);

	CreateDifferenceList(Cords1,Cords2,DifferenceList);

	cout<< "\nChecking Difference List\n---------";
	showlist(DifferenceList);

	sum = std::accumulate(DifferenceList.begin(), DifferenceList.end(), 0);
	cout << "\n Answer: "<<sum;

	
	return 0;
}