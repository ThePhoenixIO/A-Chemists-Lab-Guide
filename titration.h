#pragma once
#include <ctype.h>
#include "linkedList.h"
#include "numDescript.h"
#include "helperFunctions.h"

#ifndef titrationClass
#define titrationClass

class titration
{
public:
	// Constructors
	titration();

	// Functions
	void setGenConfig();

	void setMultiProticConfig();

	void setAnaliteConfig();

	void setTitrantConfig();

	void setVolumeConfig();

	void setOutputConfig();

	// Vars
	// Titrating a strong (s) acid or base
	bool strength;

	// Is whats in your beaker an acid (a) or base (b)
	char analite;

	// multiprotic status
	bool multiProtic;

	// number of acidic protons
	int numProtons;
	linkedList<double> kValues;

	// Analite info
	double mlAnalite;
	double molarAnalite;
	double kAnalite;

	// Titrant info
	double molarTitrant;

	// Volume info
	int numVolumes;
	linkedList<double> volumes;

	// Output digits
	int digitsToDisplay;

private:
	// Functions
	void setFlag();

	void clearFlag();

	void throwErrorMsg(const char* errorType);

	template<typename type>
	type userInput(const char* question, const char* kind, type nullValue, const char* errorCode);

	// Values
	bool flag;

	bool returnValue;

	int ordnal;

	const char* check;

};

// Constructors
titration::titration()
{
	this->returnValue = false;

	setGenConfig();
	if (!returnValue)
	{
		std::cout << "Error: unknown fatal error in setGenConfig().\n\n";
	}

	if (multiProtic)
	{
		setMultiProticConfig();
		if (!returnValue)
		{
			std::cout << "Error: unknown fatal error in setMultiProticConfig().\n\n";
		}
	}

	setAnaliteConfig();
	if (!returnValue)
	{
		std::cout << "Error: unknown fatal error in setAnaliteConfig().\n\n";
	}

	setTitrantConfig();
	if (!returnValue)
	{
		std::cout << "Error: unknown fatal error in setTitrantConfig().\n\n";
	}
	
	setVolumeConfig();
	if (!returnValue)
	{
		std::cout << "Error: unknown fatal error in setVolumeConfig().\n\n";
	}

	setOutputConfig();
	if (!returnValue)
	{
		std::cout << "Error: unknown fatal error in setOutputConfig().\n\n";
	}
}

// Private functions
inline void titration::setFlag()
{
	this->flag = true;
}

inline void titration::clearFlag()
{
	this->flag = false;
}

inline void titration::throwErrorMsg(const char* errorType)
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
inline type titration::userInput(const char* question, const char* kind, type nullValue, const char* errorCode)
{
	type input = nullValue;
	int test = -1;
	if (kind == "int")
	{
		type input = nullValue;

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
		type input = nullValue;

		do
		{
			clearFlag();

			std::printf(question, ordnal , suffix(ordnal));
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
		type input = nullValue;
		int test = -1;

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

// Public Functions
inline void titration::setGenConfig()
{
	// Vars set-up
	char input = 116;

	// User input Stong acid or Base
	this->check = "yn";
	input = userInput<char>("Is the titrant strong (y or n)?", "char", 116, "char");
	this->strength = userBoolInterplation(input);

	// User input Analite acid or base
	this->check = "ab";
	input = userInput<char>("What's in your beaker, an acid(a) or a base(b)?", "char", 116, "char");
	this->analite = input;

	// User input Multi-protic
	this->check = "yn";
	input = userInput<char>("Is this a multi-protic neurtilization (y or n)?", "char", 116, "char");
	this->multiProtic = userBoolInterplation(input);

	this->returnValue = true;
}

inline void titration::setMultiProticConfig()
{
	// Vars set-up
	int intInput = -1;
	double kValue = -1;

	// User input number of acidic protons
	intInput = userInput<int>("How many acidic protons are being neutrilized (an intiger)?", "int", -1, "int");
	this->numProtons = intInput;

	// User input k-values for protons
	for (int n = 1; n <= numProtons; n++)
	{
		this->ordnal = n;
		kValue = userInput<double>("Is the k-value of the %d%s acidic proton?\n>>", "ordnal", -1, "int");
		this->kValues.append(kValue);
	}

	this->returnValue = true;
}

inline void titration::setAnaliteConfig()
{
	double input = -1;
	// User input ml analite
	input = userInput<double>("How much analite do you have?", "int", -1, "int");
	this->mlAnalite = input;
	
	// User input M analite
	input = userInput<double>("What molar is your analite?", "int", -1, "int");
	this->molarAnalite = input;
	
	// User input k analite
	input = userInput<double>("What is the k-value for the analite?", "int", -1, "int");
	this->kAnalite = input;
	
	this->returnValue = true;
}

inline void titration::setTitrantConfig()
{
	double input = -1;
	// User input M titrant
	input = userInput<double>("What molar is your titrant?", "int", -1, "int");
	this->molarTitrant = input;

	this->returnValue = true;
}

inline void titration::setVolumeConfig()
{
	// Vars set-up
	int intInput = -1;
	double volume = -1;

	// User input number of volumes to calculate
	intInput = userInput<int>("How many volumes are you taking (an intiger)?", "int", -1, "int");
	this->numVolumes = intInput;

	// User input of volumes
	for (int n = 1; n <= numVolumes; n++)
	{
		this->ordnal = n;
		volume = userInput<double>("Is the %d%s volume?\n>>", "ordnal", -1, "int");
		this->volumes.append(volume);
	}

	this->returnValue = true;
}

inline void titration::setOutputConfig()
{
	int input = -1;
	// User input ml analite
	input = userInput<int>("How much analite do you have?", "int", -1, "int");
	this->digitsToDisplay = input;

	this->returnValue = true;
}

#endif // !titration