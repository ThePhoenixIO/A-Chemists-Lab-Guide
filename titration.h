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

	void beginCalc();

	void calculateStrong();

	void calculateWeak();

protected:
	// Calculation Functions
	void calculate_Equivalnce_PT();

	void calculate_Half_Equivalnce_PT();

	double strong_pH_calc(double volume);

	double weak_pH_ICE_calc(double volume, double constant, double kValue);

	void output(double volume, double pH, const char* selection = "NULL");

	// Calculation Vars
	double equivalancePt;

	double halfEquivalancePt;

private:
	// Lists
	linkedList<double> pH_Volumes;

	linkedList<double> pH_Values;

	// kc Constant
	double kc = 1e-14;

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
	double molAnalite;
	double kAnalite;

		// Titrant info
	double molarTitrant;

		// Volume info
	int numVolumes;
	linkedList<double> volumes;

		// Output digits
	int digitsToDisplay;

	//Functions
	void dataAppend(double pH, double volume);
};

// Constructors
titration::titration()
{
	this->returnValue = false;
	this->equivalancePt = NULL;
	this->halfEquivalancePt = NULL;

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

	//setOutputConfig();
	this->returnValue = true;
	if (!returnValue)
	{
		std::cout << "Error: unknown fatal error in setOutputConfig().\n\n";
	}
}

// Private functions
inline void titration::dataAppend(double pH, double volume)
{
	this->pH_Values.append(pH);
	this->pH_Volumes.append(volume);
}

// Public Functions
	// Set up Functions
inline void titration::setGenConfig()
{
	// Vars set-up
	char input = 116;
	system("cls");

	// User input Stong acid or Base
	input = userInput<char>("Is the titrant strong (y or n)?", "char", 116, "char", NULL, "yn");
	this->strength = userBoolInterplation(input);

	// User input Analite acid or base
	input = userInput<char>("What's in your beaker, an acid(a) or a base(b)?", "char", 116, "char", NULL, "ab");
	this->analite = input;

	// User input Multi-protic
	input = userInput<char>("Is this a multi-protic neurtilization (y or n)?", "char", 116, "char", NULL,  "yn");
	this->multiProtic = userBoolInterplation(input);

	bool checksum = false;
	input = userInput<char>("Are the above values correct (y or n)?", "char", 116, "char", NULL, "yn");
	checksum = userBoolInterplation(input);

	if (checksum == false)
	{
		setGenConfig();
	}

	this->returnValue = true;
}

inline void titration::setMultiProticConfig()
{
	// Vars set-up
	int intInput = -1;
	double kValue = -1;
	system("cls");

	// User input number of acidic protons
	intInput = userInput<int>("How many acidic protons are being neutrilized (an intiger)?", "int", -1, "int");
	this->numProtons = intInput;

	// User input k-values for protons
	for (int n = 1; n <= numProtons; n++)
	{
		kValue = userInput<double>("Is the k-value of the %d%s acidic proton?\n>>", "ordnal", -1, "int", n);
		this->kValues.append(kValue);
	}


	bool checksum = false;
	char input = userInput<char>("Are the above values correct (y or n)?", "char", 116, "char", NULL, "yn");
	checksum = userBoolInterplation(input);

	if (checksum == false)
	{
		kValues.clear();
		setMultiProticConfig();
	}

	this->returnValue = true;
}

inline void titration::setAnaliteConfig()
{
	// Vars setup
	double input = -1;
	system("cls");

	// User input ml analite
	input = userInput<double>("How much analite do you have? (in mL)", "int", -1, "int");
	this->mlAnalite = input;
	
	// User input M analite
	input = userInput<double>("What molar is your analite?", "int", -1, "int");
	this->molarAnalite = input;

	// User input k analite
	if (strength != true)
	{
		input = userInput<double>("What is the k-value for the analite?", "int", -1, "int");
		this->kAnalite = input;
	}
	else
	{
		this->kAnalite = NULL;
	}

	this->molAnalite = (mlAnalite / 1000) * molarAnalite;
	
	bool checksum = false;
	input = userInput<char>("Are the above values correct (y or n)?", "char", 116, "char", NULL, "yn");
	checksum = userBoolInterplation(input);

	if (checksum == false)
	{
		setAnaliteConfig();
	}

	this->returnValue = true;
}

inline void titration::setTitrantConfig()
{
	// Vars setu-up
	double input = -1;
	system("cls");

	// User input M titrant
	input = userInput<double>("What molar is your titrant?", "int", -1, "int");
	this->molarTitrant = input;

	bool checksum = false;
	input = userInput<char>("Are the above values correct (y or n)?", "char", 116, "char", NULL, "yn");
	checksum = userBoolInterplation(input);

	if (checksum == false)
	{
		setGenConfig();
	}

	this->returnValue = true;
}

inline void titration::setVolumeConfig()
{
	// Vars set-up
	int intInput = -1;
	double volume = -1;
	system("cls");

	// User input number of volumes to calculate
	intInput = userInput<int>("How many volumes are you taking (an intiger)?", "int", -1, "int");
	this->numVolumes = intInput;

	// User input of volumes
	for (int n = 1; n <= numVolumes; n++)
	{
		volume = userInput<double>("What is the %d%s volume (in mL)?\n>> ", "ordnal", -1, "int", n);
		this->volumes.append(volume);
	}

	bool checksum = false;
	char input = userInput<char>("Are the above values correct (y or n)?", "char", 116, "char", NULL, "yn");
	checksum = userBoolInterplation(input);

	if (checksum == false)
	{
		volumes.clear();
		setVolumeConfig();
	}

	this->returnValue = true;
}

inline void titration::setOutputConfig()
{
	int input = -1;
	// User input ml analite
	input = userInput<int>("How many digits do you wish to display?", "int", -1, "int");
	this->digitsToDisplay = input;

	this->returnValue = true;
}

	// Calculation Functions
inline void titration::beginCalc()
{
	system("cls");

	calculate_Equivalnce_PT();
	if (strength == true)
	{
		calculateStrong();
	}
	else if (strength == false)
	{
		calculate_Half_Equivalnce_PT();
		calculateWeak();
	}
	else
	{
		std::cout << "Error: beginCalc, strength" << std::endl;
	}
}

inline void titration::calculateStrong()
{
	double temp_pH;

	node<double>* currentNode = volumes.getFirst();

	for (int n = 0; n < numVolumes; n++)
	{
		double currentVolume = currentNode->data;

		if (currentVolume == 0)
		{
			temp_pH = -log10(molarAnalite);
			output(currentVolume, temp_pH);
		}

		else if (currentVolume < equivalancePt)
		{
			output(currentVolume, strong_pH_calc(currentVolume));
		}

		else if (currentVolume == equivalancePt)
		{
			output(currentVolume, 7, "eq");
		}

		else if (currentVolume > equivalancePt)
		{
			output(currentVolume, (14 - strong_pH_calc(currentVolume)));
		}

		else
		{
			std::cout << "Error: calculateStrong, n" << std::endl;
		}
		currentNode = currentNode->next;
	}
}

inline void titration::calculateWeak()
{
	double temp_pH = NULL;

	node<double>* currentNode = volumes.getFirst();	

	for (int n = 0; n < numVolumes; n++)
	{
		double currentVolume = currentNode->data;

		if (currentVolume == 0)
		{
			if (analite == 'a')
			{
				output(currentVolume, weak_pH_ICE_calc(currentVolume, molarAnalite, kAnalite));
			}
			else if (analite == 'b')
			{
				output(currentVolume, (14 - weak_pH_ICE_calc(currentVolume, molarAnalite, kAnalite)));
			}
			else
			{
				std::cout << "Error: calculateWeak, currentVolume == 0, analite" << std::endl;
			}
		}

		else if (currentVolume < equivalancePt)
		{
			if (currentVolume == halfEquivalancePt)
			{
				if (analite == 'a')
				{
					temp_pH = -log10(kAnalite);
				}
				else if (analite == 'b')
				{
					temp_pH = -log10(kc);
				}
				else
				{
					std::cout << "Error: calculateWeak, currentVolume < equivalancePt, currentVolume == halfEquivalancePt, analite" << std::endl;
				}

				output(currentVolume, temp_pH, "heq");
			}
			else
			{
				double molTitarnt = ((currentVolume / 1000) * molarTitrant);
				
				if (analite == 'a')
				{
					output(currentVolume, (-log10(kAnalite) + log10((molTitarnt / (molAnalite - molTitarnt)))));
				}
				else if (analite == 'b')
				{
					output(currentVolume, (-log10(kAnalite) + log10(((molAnalite - molTitarnt) / molTitarnt))));
				}
				else
				{
					std::cout << "Error: calculateWeak, currentVolume < equivalancePt, else, analite" << std::endl;
				}
			}
		}

		else if (currentVolume == equivalancePt)
		{
			if (analite == 'a')
			{
				output(currentVolume, (14 - weak_pH_ICE_calc(currentVolume, (molAnalite / ((mlAnalite + equivalancePt) / 1000)), kAnalite)), "eq");
			}
			else if (analite == 'b')
			{
				output(currentVolume, weak_pH_ICE_calc(currentVolume, (molAnalite / ((mlAnalite + equivalancePt) / 1000)), kAnalite), "eq");
			}
			else
			{
				std::cout << "Error: calculateWeak, currentVolume == equivalancePt, analite" << std::endl;
			}
		}

		else if (currentVolume > equivalancePt)
		{
			if (analite == 'a')
			{
				output(currentVolume, (14 - (-log10(((((currentVolume - equivalancePt) / 1000) * molarTitrant) / ((mlAnalite + currentVolume) / 1000))))));
			}
			else if (analite == 'b')
			{
				output(currentVolume, (-log10(((((currentVolume - equivalancePt) / 1000) * molarTitrant) / ((mlAnalite + currentVolume) / 1000)))));
			}
			else
			{
				std::cout << "Error: calculateWeak, currentVolume > equivalancePt, analite" << std::endl;
			}
		}

		else
		{
			std::cout << "Error: calculateStrong, n" << std::endl;
		}

		currentNode = currentNode->next;
	}
}

//Protected Functions
inline void titration::calculate_Equivalnce_PT()
{
	this->equivalancePt = ((molarAnalite * mlAnalite) / molarTitrant);
	bool returnValue = volumes.insert(equivalancePt);
	if (returnValue)
	{
		this->numVolumes++;
	}
}

inline void titration::calculate_Half_Equivalnce_PT()
{
	this->halfEquivalancePt = ((0.5 * molarAnalite * mlAnalite) / molarTitrant);
	bool returnValue = volumes.insert(halfEquivalancePt);
	if (returnValue)
	{
		this->numVolumes++;
	}
}

inline double titration::strong_pH_calc(double volume)
{
	double molTitrant = (volume / 1000) * molarTitrant;
	double molDifference = abs(molAnalite - molTitrant);
	double molarTitrant = molDifference / ((mlAnalite + volume) / 1000);
	double pH = -log10(molarTitrant);

	return pH;
}

inline double titration::weak_pH_ICE_calc(double volume, double constant, double kValue)
{
	double moles = NULL;
	double soln1 = (-kValue + sqrt(pow(kValue, 2) - 4 * -(kValue * constant)));
	double soln2 = (-kValue - sqrt(pow(kValue, 2) - 4 * -(kValue * constant)));

	if (soln1 > 0)
	{
		moles = soln1;
	}
	else if (soln2 > 0)
	{
		moles = soln2;
	}
	else
	{
		std::cout << "Error: weak_pH_ICE_calc, ans" << std::endl;
	}

	double pH = -log10(moles);

	return pH;
}

inline void titration::output(double volume, double pH, const char* selection)
{
	const char* endString = "NULL";

	if (selection == "NULL")
	{
		endString = "\n";
	}
	else if (selection == "eq")
	{
		endString = "<-- Equivalence Point\n";
	}
	else if (selection == "heq")
	{
		endString = "<-- Half-Equivalence Point\n";
	}

	printf("pH at %fmL: %f %s",  volume, pH, endString);
	dataAppend(pH, volume);
}
#endif // !titration