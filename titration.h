#pragma once
#include <ctype.h>
#include "linkedList.h"
#include "helperFunctions.h"
#include "input.h"

#ifndef titrationClass
#define titrationClass

class titration: private input
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

// Public Functions
inline void titration::setGenConfig()
{
	// Vars set-up
	char input = 116;

	// User input Stong acid or Base
	input = userInput<char>("Is the titrant strong (y or n)?", "char", 116, "char", NULL, "yn");
	this->strength = userBoolInterplation(input);

	// User input Analite acid or base
	input = userInput<char>("What's in your beaker, an acid(a) or a base(b)?", "char", 116, "char", NULL, "ab");
	this->analite = input;

	// User input Multi-protic
	input = userInput<char>("Is this a multi-protic neurtilization (y or n)?", "char", 116, "char", NULL,  "yn");
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
		kValue = userInput<double>("Is the k-value of the %d%s acidic proton?\n>>", "ordnal", -1, "int", n);
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
		volume = userInput<double>("Is the %d%s volume?\n>>", "ordnal", -1, "int", n);
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