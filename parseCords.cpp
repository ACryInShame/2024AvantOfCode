#include <string>
#include <list>
using namespace std;

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