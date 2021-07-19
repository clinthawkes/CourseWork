/**********************************************************************************
 ** Name:			Clinton Hawkes
 ** Date:			01/13/2019
 ** Description:	Asks user to input a temperature in celcius, converts the
 **					temperature to fahrenheit and then print it out.
 **********************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main ()
{
	double fTemp,		//fahrenheit temperature variable
		   cTemp;		//celsius temperature variable
    
    //assigns user's input to cTemp variable 
	cout << "Please enter a Celsius temperature." << endl;
	cin >> cTemp;

	//converts celsius to fahrenheit using formula F = 1.8C + 32	
	fTemp = 1.8 * cTemp + 32;
    
	//prints out the celsius temperature as fahrenheit 
	cout << "The equivalent Fahrenheit temperature is:\n" << fTemp << endl;

	return 0;
}
