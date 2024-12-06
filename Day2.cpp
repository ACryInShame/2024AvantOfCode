// Functions used for day 2 of Advant of code 2024
#include <string>
#include <list>
using namespace std;

void parseReports (string input, list<int>& list1)
{
   string holdString; //holds current string;
   string tempInput = input;
   int tempInt; // Holds current number

   // run through each line in input and pull it into list1
   for (int i=0;tempInput.size()>1;i++)
   {
      //find the first new line and add it to list1
      tempInt = tempInput.find('\n');
      holdString = tempInput.substr(0,tempInt);

      // put line  into the list
      list1.push_back(stoi(holdString));

      //remove the line from the string by subsring just past it (+1)
      tempInput = tempInput.substr(tempInt+1);
   };
}