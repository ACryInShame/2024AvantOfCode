#pragma once
#include <list>
#include <algorithm>
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