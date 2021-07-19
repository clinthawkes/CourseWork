/*******************************************************************************************
 * Name:			Clinton Hawkes
 * Date:			01/13/2019
 * Description:		Asks user to enter an amount of change less than a dollar but greater
 * 					than zero, calculates how many coins represent that amount with the 
 * 					fewest number of coins and then prints it out.
 ******************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main ()
{
	const int QUARTER = 25,		//value of a quarter
			  DIME = 10,		//value of a dime
			  NICKEL = 5;		//value of a nickel
	
	int cents;					

	//assigns value to variable cents	
	cout << "Please enter an amount in cents less than a dollar." << endl;
	cin >> cents;

	cout << "Your change will be:\n";
	cout << "Q: " << (cents / QUARTER) << endl;     //calcs number of quarters and prints
	cents %= QUARTER;								//removes value in quarters from cents

	cout << "D: " << (cents / DIME) << endl;        //calcs number of dimes and prints
	cents %= DIME;									//removes value in dimes from cents
	
	cout << "N: " << (cents / NICKEL) << endl;      //calcs number of nickels and prints
	cents %= NICKEL;								//removes value in nickels from cents
	
	cout << "P: " << cents << endl;					//prints out value of cents for pennys


	return 0;
}
//Please write in the comments if I am using too many comments. Thanks.
