/**************************************************************************************
 * Name:        Clinton Hawkes
 * Date:        01/19/2019
 * Description: Prompts user to enter a number that self or others will try to guess.
 *              If the guess is too high or too low, a message will print out telling 
 *              them. After a correct guess is entered, the number of times it took to
 *              guess will be printed on the screen.
 *************************************************************************************/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;   

int main()
{
    int target,         //declaring int variables used in this program
        guess,
        count=0;

    //gets the integer that another player will guess    
    cout << "Enter the number for the player to guess." << endl;
    cin >> target;
    
    //asks for the other player's guess  
    cout << "Enter your guess." << endl;

    //loop continues to ask for and evaluate guesses until it matches target  
    while (guess != target)
    {
        cin >> guess;

        //tells player whether they are too high or too low 
        if (guess > target)
            cout << "Too high - try again." << endl;
        else if (guess < target)
            cout << "Too low - try again." << endl;

        count++;
    }
    
    //after guess is correct, this prints the number of tries it took 
    cout << "You guessed it in " << count << " tries." << endl;
     
    return 0;
}

