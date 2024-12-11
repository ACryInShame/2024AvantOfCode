#pragma once
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "ReadFile.cpp"
#include "TestMessage.cpp"
using namespace std;

//Functions
int parseCorruptedData (string input);
bool isNumber (string input);


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
	int ProductSum = parseCorruptedData(fileInfo);
   cout<< "Product Sum:" + to_string(ProductSum);

}

//clean up the currupted data
int parseCorruptedData (string input)
{
   string tempString; // The string currently being tested
   string numberString; //string to hold possible number
   int maxSequenceSize = 12; //the max size of the sequence expected (mul(XXX,XXX))
   int startPOS; //start position of a substring
   int stringLength; //length of a substring
   int number1; //1st number in sequence
   int number2; //2nd sunber in sequence
   int product; // product of number1 and number2
   int ProductSum = 0; //sum of all the product numbers

   do
   {
      TestMessage("Loop\n-----\n");

      //find mul(XXX,XXX) sequence
      if (input.find("mul(") == string::npos) //test for not found
         break;
      startPOS = input.find("mul(");
      tempString = input.substr(startPOS,maxSequenceSize);
      TestMessage("tested sequence: " + tempString + "\n");

      //remove string up to sequence as it's no longer needed
      input = input.substr(startPOS+1);
      TestMessage("input shortened\n");

      //find ',' and get length of substring;
      if (tempString.find(",") == string::npos) //test for not found
         continue;
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
         continue;

      //found 1st number
      number1 = stoi(numberString);
      //find ')' after ',' and get the length
      if (tempString.find(")") == string::npos) //test for not found
         continue;
      startPOS = tempString.find(",")+1;
      stringLength = tempString.find(")") - startPOS;

      //create substring between ',' and ')' and test if it's a number
      numberString = tempString.substr(startPOS,stringLength);
      TestMessage("Number string: " + numberString + "\n");
      if (!isNumber(numberString))
         continue;

      //found second number
      number2 = stoi(numberString);

      product = number1 * number2;
      TestMessage("product: " + to_string(product) + "\n");
      ProductSum += product;
      TestMessage("ProductSum: " + to_string(ProductSum) + "\n");

      //remove sequence from input string
      input =input.substr(tempString.find(")"));

   }
   while (true);

   return ProductSum;
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