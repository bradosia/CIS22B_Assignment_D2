/*
Branden Lee
CIS 22B
Fall 2017
Assignment D
Problem D2

Used Microsoft Visual Studio 2017

Car class
Reads data from "data.txt" and prints it.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>      // std::fstream
#include <stdio.h>
using namespace std;

/**************************************************
** global functions, and variables
**************************************************/

void input ();

/**************************************************
** Car class
**************************************************/
class Car
{
private:
	string reportingMark;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
public:
	Car () { setup ("", 0, "other", false, "NONE"); } //default constructor
	Car (const Car *CarObj) { setup (CarObj->reportingMark, CarObj->carNumber, CarObj->kind, CarObj->loaded, CarObj->destination); } //copy constructor
	Car (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit) { setup (reportingMarkInit, carNumberInit, kindInit, loadedInit, destinationInit); } //other constructor
	~Car () {} // destructor
	void setup (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit);
	void output ();
	friend bool Car::operator==(const Car CarObj1, const Car CarObj2)
	{
		if (CarObj1.reportingMark == CarObj2.reportingMark && CarObj1.carNumber == CarObj2.carNumber&& CarObj1.kind == CarObj2.kind&& CarObj1.loaded == CarObj2.loaded&& CarObj1.destination == CarObj2.destination) { return true; }
		return false;
	}
};

int main ()
{
	input ();
	system ("pause");
	return 0;
}

/**************************************************
** Car class method definitions
**************************************************/

/******************* Car::setup *******************
** Puts the car data into the object
**************************************************/
void Car::setup (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit)
{
	reportingMark = reportingMarkInit;
	carNumber = carNumberInit;
	kind = kindInit;
	loaded = loadedInit;
	destination = destinationInit;
}

/********************* Car::output ****************
** Prints the car data in a neat format
**************************************************/
void Car::output ()
{
	// cout << bool will output an integer
	// we create a temporary string to output the bool
	// std::boolalpha can also be used
	string loadedString = (!loaded) ? "false" : "true";
	cout << setw (16) << left << "reportingMark:" << reportingMark << endl
		<< setw (16) << left << "carNumber: " << carNumber << endl
		<< setw (16) << left << "kind: " << kind << endl
		<< setw (16) << left << "loaded: " << loadedString << endl
		<< setw (16) << left << "destination: " << destination << endl << endl;
}

/**************************************************
** global function definitions
**************************************************/

/********************* input **********************
** Reads the car data from the text file "data.txt"
** Prints data from the file
**************************************************/
void input ()
{
	string carType, reportingMarkInit, kindInit, destinationInit, loadedInit;
	int carNumberInit;
	std::fstream inputFile;
	inputFile.open ("data.txt");
	if (!inputFile)
	{
		cerr << "File could not be opened." << endl;
		exit (1);
	}
	while (inputFile.peek () != EOF)
	{
		while (inputFile.peek () == ' ')
			inputFile.get ();
		inputFile >> carType >> reportingMarkInit >> carNumberInit >> kindInit >> loadedInit;
		while (inputFile.peek () == ' ')
			inputFile.get ();
		getline (inputFile, destinationInit);
		// If the carType is not "Car", send an error message and do nothing.
		if (carType == "Car")
		{
			// If the carType is "Car", declare a Car object named temp using the constructor that takes 5 parameters.
			Car temp (reportingMarkInit, carNumberInit, kindInit, loadedInit=="true"?true:false, destinationInit);
			temp.output ();
		}
		// If the carType is not "Car", send an error message and do nothing.
		else cerr << "Not a car" << endl;
	}
	inputFile.close ();
}

/* Execution results
reportingMark:  CN
carNumber:      819481
kind:           maintenance
loaded:         false
destination:    NONE

reportingMark:  SLSF
carNumber:      46871
kind:           business
loaded:         true
destination:    Memphis

reportingMark:  AOK
carNumber:      156
kind:           tender
loaded:         true
destination:    McAlester
*/