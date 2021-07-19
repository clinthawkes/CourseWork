/**************************************************************************************************
** Program Name:Lab 10
** Author:      Clinton Hawkes
** Date:        06/04/2019
** Description: Main function for testing the  
**************************************************************************************************/

#include "fibRec.hpp"
#include "fibNonRec.hpp"
#include "validation.hpp"
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;

int main(){

    clock_t t;              //used to calculate time taken to complete calculation
    long fib = 0;           //stores the fibonacci term value
    int num = 0;            //stores the term input by user
    bool state = true;
    
    system("clear"); 

    while(state == true){

        cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl; 
        cout << "What fibonacci term do you want to find? (0 .. 100)" << endl;
        cout << "Number: ";
        num = integerValidation(0, 100);
        
        t = clock();                //starts timer     
        fib = fibNonRec(num);       //using iteration to find term
        cout << "\nFibonacci term " << num << " using iteration is " << fib << "." << endl;
        t = clock() - t;            //stops timer and saves amount of time function took
        cout << "Iteration took " << t << " ticks to calculate." << endl;
        
        t = clock();                //starts timer
        fib = fibRec(num);          //using recursive function to find term
        cout << "\nFibonacci term " << num << " using recursion is " << fib << "." << endl;
        t = clock() - t;            //stops timer and saves amount of time function took
        cout << "Recursion took " << t << " ticks to calculate." << endl;
        
        cout << "\n1 to run again, 0 to quit" << endl;
        cout << "Selection: ";
        state = integerValidation(0, 1);
    }

    return 0;
}
