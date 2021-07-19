/********************************************************************************
 ** Name:			Clint Hawkes
 ** Date: 			01/13/2019
 ** Description:	Asks user to input 5 numbers, calculates the average, and
 ** 				then prints it out on the screen.
********************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    // Declares variables used 
	double varOne, varTwo, varThree, varFour, varFive, varAvg;
					   
	// Assigns user's values to variables	
	cout << "Please enter five numbers." << endl;
	cin >> varOne >> varTwo >> varThree >> varFour >> varFive;
	
	// Compute mean value
	varAvg = (varOne + varTwo + varThree + varFour + varFive) / 5;

	// Prints out mean value	
	cout << "The average of those numbers is:\n" << varAvg << endl;
	
	return 0;
}

