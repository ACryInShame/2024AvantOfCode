#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string readFile(string fileName)
{
   string line; // holds the current line being read
   string outputString; // String to add each line to from file'

   // opens file
   std::ifstream file(fileName);

   // test if file path is valid
   if (!file) 
   {
        std::cerr << "Unable to open file\n";
        return "";
   }

   //Check each line and add it to the outputString
   while (getline(file, line))
   {
      outputString += line + "\n";
   }
   return outputString;
};