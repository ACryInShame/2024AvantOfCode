#pragma once
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "ReadFile.cpp"
#include "TestMessage.cpp"
using namespace std;

//Functions
int parseCorruptedData (string,bool);
bool isNumber (string input);
int processMul (string tempString, int startPOS);


void Day3Part1 ()
{
   	string FileName;
	if (Testing)
	FileName = "Puzzles\\AdventDay3 - TEST.txt";
	else
	FileName = "Puzzles\\AdventDay3.txt";

	cout << "reading file\n--------\n";
	string fileInfo = readFile(FileName);
   cout<< fileInfo << endl;

   
	cout<< "parsing file\n---------\n";
	int ProductSum = parseCorruptedData(fileInfo,false);
   cout<< "Product Sum:" + to_string(ProductSum);

}
//-------------------------------------------------------------
void Day3Part2 ()
{
   	string FileName;
	if (Testing)
	FileName = "Puzzles\\AdventDay3 - TEST.txt";
	else
	FileName = "Puzzles\\AdventDay3.txt";

	cout << "reading file\n--------\n";
	string fileInfo = readFile(FileName);
   cout<< fileInfo << endl;

   
	cout<< "parsing file\n---------\n";
	int ProductSum = parseCorruptedData(fileInfo,true);
   cout<< "Product Sum:" + to_string(ProductSum);

}
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//clean up the currupted data
int parseCorruptedData (string input,bool Part2)
{
   string tempString; // The string currently being tested
   int maxSequenceSize = 12; //the max size of the sequence expected (mul(XXX,XXX))
   int startPOS; //start position of a substring
   int ProductSum = 0; //sum of all the product numbers
   bool enabled = true; // are we reading mul(#,#) statements?


   do
   {
      TestMessage("Loop\n-----\n");
      // used to see which sequence is next
      int doLoc = input.find("do()");
      int dontLoc = input.find("don't()");
      int mulLoc = input.find("mul(");
      int nextSequenceLoc;
      TestMessage("do, dont, mul:"+ to_string(doLoc) + " " + to_string(dontLoc) + " " + to_string(mulLoc) + "\n");

      //test if at end of file, or if one sequence is no longer found
      if (doLoc == -1 && doLoc == -1 && mulLoc == -1)
         break;
      if (doLoc == -1)
         doLoc = input.size();
      if (dontLoc == -1)
         dontLoc = input.size();
      if (mulLoc == -1)
         mulLoc = input.size();

      //find next sequence      
      if (enabled && (mulLoc < doLoc || doLoc == -1) && (mulLoc < dontLoc || dontLoc == -1)) //if processing mul()
      {
            nextSequenceLoc = mulLoc;

            //process mul()
            TestMessage("Processing mul\n");
            if (mulLoc == string::npos) //test for not found
               break;
            startPOS = mulLoc;
            tempString = input.substr(startPOS,maxSequenceSize);
            TestMessage("tested sequence: " + tempString + "\n");

            ProductSum += processMul(tempString,startPOS);
            TestMessage("ProductSum: " + to_string(ProductSum) + "\n");
      }else if (doLoc < dontLoc)
      {
         TestMessage("Processing do\n");
         if (Part2)
            enabled = true;//process do  
         nextSequenceLoc = doLoc;
      }
      else
      {
         TestMessage("Processing don't\n");
         if (Part2)
            enabled = false;//process don't
         nextSequenceLoc = dontLoc; 
      }   

      //remove string up to sequence as it's no longer needed
      input = input.substr(nextSequenceLoc+1);
      TestMessage("input shortened\n");
   }
   while (true);

   return ProductSum;
}

int processMul (string tempString, int startPOS)
{
   int stringLength; //length of a substring
   int number1; //1st number in sequence
   int number2; //2nd sunber in sequence
   int product; // product of number1 and number2
   string numberString; //string to hold possible number

   //find ',' and get length of substring;
   if (tempString.find(",") == string::npos) //test for not found
      return 0;
   startPOS = tempString.find("(")+1; // moves past the 'mul('
   stringLength = tempString.find(",");
   stringLength -= startPOS;
   TestMessage("found ','\n");
   TestMessage("startPOS: "+to_string(startPOS)+ "\n");
   TestMessage("stringLength: " + to_string(stringLength)+ "\n");

   //create substring between sequence and ',' and test if it's a number
   numberString = tempString.substr(startPOS,stringLength);
   TestMessage("Number string: " + numberString + "\n");
   if (!isNumber(numberString))
      return 0;

   //found 1st number
   number1 = stoi(numberString);
   //find ')' after ',' and get the length
   if (tempString.find(")") == string::npos) //test for not found
      return 0;
   startPOS = tempString.find(",")+1;
   stringLength = tempString.find(")") - startPOS;

   //create substring between ',' and ')' and test if it's a number
   numberString = tempString.substr(startPOS,stringLength);
   TestMessage("Number string: " + numberString + "\n");
   if (!isNumber(numberString))
      return 0;

   //found second number
   number2 = stoi(numberString);

   product = number1 * number2;
   TestMessage("product: " + to_string(product) + "\n");
   return product;
}

//check if given string input in a number
bool isNumber (string input)
{
   for (int i=0; i < input.size();i++)
   {
      if (!isdigit(input[i]))
         return false;
   }
   return true;
}