#pragma once
#include <vector>
#include <cmath>
#include "ReadFile.cpp"
#include "TestMessage.cpp"
using namespace std;

enum Direction
{
   UpLeft,
   Up,
   UpRight,
   Left,
   Right,
   DownLeft,
   Down,
   DownRight
};

vector<vector<char>> parsingToMatrix (string input);
int wordSearch(string word);
int XwordSearch(string word);
int findWord (int Row,int Col,string word,Direction D);
vector<vector<char>> WordPuzzle;


void Day4Part1 ()
{
   string FileName;
	if (Testing)
	   FileName = "Puzzles\\AdventDay4 - TEST.txt";
	else
	   FileName = "Puzzles\\AdventDay4.txt";

	cout << "reading file\n--------\n";
	string fileInfo = readFile(FileName);
   cout<< fileInfo << endl;

   cout<< "parsing file to Array\n---------\n";
   WordPuzzle = parsingToMatrix(fileInfo);

   TestMessage("---WordPuzzle---\n");
   if (Testing == true)
   {
      for (int i = 0; i < WordPuzzle.size(); i++) 
      {
        for (int j = 0; j < WordPuzzle[0].size(); j++) 
        {
            TestMessage(string(1,WordPuzzle[i][j]));
        }
        TestMessage("\n");
      }
   }

   int count = wordSearch("XMAS");
   cout<< "XMAS appears " << count<< " Times";
}

void Day4Part2 ()
{
   string FileName;
	if (Testing)
	   FileName = "Puzzles\\AdventDay4 - TEST.txt";
	else
	   FileName = "Puzzles\\AdventDay4.txt";

	cout << "reading file\n--------\n";
	string fileInfo = readFile(FileName);
   cout<< fileInfo << endl;

   cout<< "parsing file to Array\n---------\n";
   WordPuzzle = parsingToMatrix(fileInfo);

   TestMessage("---WordPuzzle---\n");
   if (Testing == true)
   {
      for (int i = 0; i < WordPuzzle.size(); i++) 
      {
        for (int j = 0; j < WordPuzzle[0].size(); j++) 
        {
            TestMessage(string(1,WordPuzzle[i][j]));
        }
        TestMessage("\n");
      }
   }

   int count = XwordSearch("MAS");
   cout<< "MAS appears " << count<< " Times";

}

vector<vector<char>> parsingToMatrix (string input)
{
   vector<vector<char>> matrix; // full matrix to be returned 
   vector<char> tempRow; // temp row that will fill and then add to matrix

   //check each character and add to the row. 
   //when line break is found, add row to matrix clear temp row and continue
   for (char C: input)
   {
      if (C == '\n')
      {
         TestMessage("\nfound line break\n");
         matrix.push_back(tempRow);
         tempRow.clear();
      }
      else
      {
         tempRow.push_back (C);
         TestMessage(string(1, C));
      }
   }

   return matrix;
}

int wordSearch(string word)
{
   int count=0; // number of times word is found

   TestMessage("--wordSearch--\n");
   //get first letter of the word
   char firstLetter = word[0];

   //check each 
   for (int row = 0; row < WordPuzzle.size(); row++) 
   {
      for (int col = 0; col < WordPuzzle[0].size(); col++) 
      {
         if(WordPuzzle[row][col] == firstLetter)
         {
            //after letter is found check all 8 directions for word
            TestMessage("Found Letter\n");
            count += findWord(row,col,word,UpLeft);
            count += findWord(row,col,word,Up);
            count += findWord(row,col,word,UpRight);
            count += findWord(row,col,word,Left);
            count += findWord(row,col,word,Right);
            count += findWord(row,col,word,DownLeft);
            count += findWord(row,col,word,Down);
            count += findWord(row,col,word,DownRight);
         }   
      }
      TestMessage("\ncount:" + to_string(count) + "\n");
   }
   return count;
}

int findWord (int row,int col,string word,Direction D)
{
   TestMessage("Location:" + to_string(row) +"," + to_string(col) + "\n");
   // what to add to row and col to match direction
   int plusRow;
   int plusCol;
   switch (D){
   case UpLeft:
      plusRow = -1;
      plusCol = -1;
      TestMessage("going UpLeft\n"); 
   break;
   case Up:
      plusRow = -1;
      plusCol = 0;
      TestMessage("going Up\n");
   break;
      case UpRight:
      plusRow = -1;
      plusCol = 1;
      TestMessage("going UpRight\n");
   break;
      case Left:
      plusRow = 0;
      plusCol = -1;
      TestMessage("going Left\n");
   break;
      case Right:
      plusRow = 0;
      plusCol = 1;
      TestMessage("going Right\n");
   break;
   case DownLeft:
      plusRow = 1;
      plusCol = -1;
      TestMessage("going DownLeft\n");
   break;
         case Down:
      plusRow = 1;
      plusCol = 0;
      TestMessage("going Down\n");
   break;
         case DownRight:
      plusRow = 1;
      plusCol = 1;
      TestMessage("going DownRight\n");
   break;   
   default:
      TestMessage("Direction Failed\n");
   break;
   }

   //get size of matrix for checks
   int numRows = WordPuzzle.size();
   int numCols = WordPuzzle[0].size(); //-2 to remove endline

   //check for each letter in word
   for (char C: word)
   {
      //check if inside matrix
      if (row >= 0 && row < numRows && col >= 0 && col < numCols)
      {
         // check if char matches
         if (WordPuzzle[row][col] == C)
         {
            TestMessage("found a letter\n");
            row += plusRow;
            col += plusCol;
         }
         else // word not found
            {
               TestMessage("letter doesn't match\n");
               return 0;
            }
      }else // outside bounds, word not found
      {
         TestMessage("outside bounds:" + to_string(row) +"," + to_string(col) + "\n");
         return 0;
      }
   }

   return 1; // if loop finishes then word was found
}

// finds a word in a matrix that crosses over itself. only works with odd length words
int XwordSearch(string word)
{
   // if words has even letters, return 0
   if (word.size()%2==0)
      return 0;
   
   int count=0; // number of times word is found
   int middleLoc = word.size()/2; // middle letter of word (will found down but strings are an array so this works)


   TestMessage("--XwordSearch--\n");
   TestMessage("Middle pos:"+ to_string(middleLoc) + "\n");
   //get first letter of the word
   char firstLetter = word[0];
   TestMessage("First Letter:"+ string(1, firstLetter) + "\n");
   int offset = middleLoc*2;//middleLoc*2 to get distance from other corners

   //check each letter in matrix (WordPuzzle)
   for (int row = 0; row < WordPuzzle.size(); row++) 
   {
      for (int col = 0; col < WordPuzzle[0].size(); col++) 
      {
         // if letter checked equals the first letter then check if it crosses
         if(WordPuzzle[row][col] == firstLetter)
         {
            //after letter is found check diagnal directions for word
            // if found (returned 1) then search again but new locations being 
            // oposite corners (if the full crossing words was a box)
            //Box example
            //M S
            // A
            //M S
            TestMessage("Found Letter:"+to_string(row)+","+to_string(col)+"\n");
            if (findWord(row,col,word,UpLeft) == 1) //Bottom right conner of box
            {
               //if a second word is found then they cross
               if (findWord(row-offset,col,word,DownLeft) == 1) // check top right
                  {
                     TestMessage("Found Cross:A\n");
                     count ++;
                  }
               if (findWord(row,col-offset,word,UpRight) == 1) //check bottom left
                  {
                     TestMessage("Found Cross:B\n");
                     count ++;
                  }
            }
            if (findWord(row,col,word,UpRight) == 1) //Bottom Left conner of box
            {
               //if a second word is found then they cross
               if (findWord(row-offset,col,word,DownRight) == 1) //check top left
                  {
                     TestMessage("Found Cross:C\n");
                     count ++;
                  }
               if (findWord(row,col+offset,word,UpLeft) == 1) //check bottom right
                  {
                     TestMessage("Found Cross:D\n");
                     count ++;
                  }
            } 
            if (findWord(row,col,word,DownLeft) == 1) //Top right conner of box
            {
               //if a second word is found then they cross
               if (findWord(row+offset,col,word,UpLeft) == 1) //check bottom right
                  {
                     TestMessage("Found Cross:E\n");
                     count ++;
                  }
               if (findWord(row,col-offset,word,DownRight) == 1) //check top left
                  {
                     TestMessage("Found Cross:F\n");
                     count ++;
                  }
            }
            if (findWord(row,col,word,DownRight) == 1) //top left conner of box
            {
               //if a second word is found then they cross
               if (findWord(row+offset,col,word,UpRight) == 1) //check bottom Left
                     {
                        TestMessage("Found Cross:G\n");
                        count ++;
                     }
               else if (findWord(row,col+offset,word,DownLeft) == 1) //check top right
                     {
                        TestMessage("Found Cross:H\n");
                        count ++;
                     }
            }
         }   
      }
      TestMessage("\ncount:" + to_string(count) + "\n");
   }
   //the count counts each crossing twice as each instance of a word triggers a check
   count = count /2;
   return count;
}