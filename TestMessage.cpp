#pragma once
#include <iostream>

bool Testing = false;

void TestMessage (string Message)
{
	if (Testing == true)
		cout << Message;
}