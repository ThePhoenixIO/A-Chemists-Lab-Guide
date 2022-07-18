#pragma once
#include <iostream>

#ifndef USERYNINPUT
#define USERYNINPUT

bool userBoolInterplation(char input)
{
	if (input == 89 || input == 121 || input == 78 || input == 110)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ynUserInCheck(char input)
{
	if (input == 89 || input == 121 || input == 78 || input == 110)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool abUserInCheck(char input)
{
	if (input == 97 || input == 65 || input == 98 || input == 66)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif // !USERYNINPUT