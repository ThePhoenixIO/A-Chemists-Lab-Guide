#pragma once
#include <iostream>
#include "numDescript.h"

#ifndef INPUT
#define INPUT

class input
{
public:
	// Constructors
	input();

protected:
	// Vars
	bool flag;

	bool returnValue;

	int ordnal;

	const char* check;

	// Functions
	void setFlag();

	void clearFlag();

	void throwErrorMsg(const char* errorType);

	template<typename type>
	type userInput(const char* question, const char* kind, type nullValue, const char* errorCode, int ordnal = 0, const char* check = "NULL");
};

input::input()
{
	this->flag = false;

	this->returnValue = false;

	this->ordnal = -1;

	this->check = "NULL";
}

inline void input::setFlag()
{
	this->flag = true;
}

inline void input::clearFlag()
{
	this->flag = false;
}

inline void input::throwErrorMsg(const char* errorType)
{
	if (errorType == "yn")
	{
		std::cout << "Error: a charachter other then y,Y,n,N was entered.\nPlase enter either y,Y,n,N.\n\n";
	}
	else if (errorType == "ab")
	{
		std::cout << "Error: a charachter other then a,A,b,B was entered.\nPlase enter either a,A,b,B.\n\n";
	}
	else if (errorType == "int")
	{
		std::cout << "Error: a character was entered instead of a number.\nPlase enter a number.\n\n";
	}
	else if (errorType = "char")
	{
		std::cout << "Error: a number was entered instead of a character.\nPlase enter a character.\n\n";
	}
	else
	{
		std::cout << "Error: unknown fatal error.\n\n";
	}
}

template<typename type>
inline type input::userInput(const char* question, const char* kind, type nullValue, const char* errorCode, int ordnal, const char* check)
{
	type input = nullValue;
	int test = -1;
	if (kind == "int")
	{
		do
		{
			clearFlag();
			std::cout << question << "\n>>";
			std::cin >> input;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throwErrorMsg(errorCode);
				setFlag();
			}
		} while (flag);

		return input;
	}
	else if (kind == "ordnal")
	{
		do
		{
			clearFlag();

			std::printf(question, ordnal, suffix(ordnal));
			std::cin >> input;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throwErrorMsg(errorCode);
				setFlag();
			}
		} while (flag);

		return input;
	}
	else if (kind == "char")
	{
		do
		{
			clearFlag();
			input = nullValue;
			test = -1;

			std::cout << question << "\n>>";
			std::cin >> input;

			test = std::isalpha(input);

			if (test == 0)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				setFlag();
				throwErrorMsg(errorCode);
			}

			if (check == "yn" && flag != true)
			{
				if (!ynUserInCheck(input))
				{
					setFlag();
					throwErrorMsg("yn");
				}
			}
			else if (check == "ab" && flag != true)
			{
				if (!abUserInCheck(input))
				{
					setFlag();
					throwErrorMsg("ab");
				}
			}
		} while (flag);

		return input;
	}
}

#endif // !INPUT

