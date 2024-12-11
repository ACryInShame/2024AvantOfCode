#include <algorithm>
#include "ReadFile.cpp"
#include "Day2.cpp"
//#include "TestMessage.cpp"
using namespace std;

int safeCount = 0;


int main()
{
	list<list<int>> DynamicArray;

	cout << "\n reading file\n--------";
	string fileInfo = readFile("Puzzles\\AdventDay2.txt");

	cout<< "\n parsing file\n---------";
	parseReports(fileInfo, DynamicArray);

	// Check every set of reports and report back safe (1) or unsafe (0). 
	// Keep count of safe reports
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