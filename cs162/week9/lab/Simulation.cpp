/**************************************************************************************************
** Program Name:STL Stack and Queue
** Author:      Clinton Hawkes
** Date:        05/29/2019
** Description: Implementation file for the Simulation class. There are two simulations available
                for the user to choose. The first is a buffer simulation. The buffer simulation
                uses a queue to act as a buffer as values are added and removed randomly from
                it. The second simulation is a palindrome maker. The user enters a string into
                the prompt and the program returns that string as a palindrome. Details of the
                functions used to implement these simulations can be found below.
**************************************************************************************************/

#include "Simulation.hpp"
#include "menu.hpp"
#include "validation.hpp"
#include <list>
#include <iomanip>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;

//default constructor
Simulation::Simulation(){
}

/**************************************************************************************************
** Description: Function acts as the director for the program. The menu is displayed and the user
                selects the option they want, the selection is passed back to this function and
                the proper function calls are made based off the user's choice. This repeats
                until the user chooses to quit the program.
**************************************************************************************************/
void Simulation::run(){

    int input = 0;              //stores the user's choice
    bool state = true;          //simulation runs until this is false
    std::string word; 

    while(state == true){

        input = menu();         //menu is called and user selects an option

        switch(input){
            
            //if user chose option 1, the buffer simulation runs 
            case 1: this->buffer();
                    break;

            //if user chose option 2, the palindrome simulation runs 
            case 2: word = this->palindrome();
                    break;

            //if user chose option 3, the program terminates 
            case 3: state = false;
                    break;
                
        }                
    } 
}

/**************************************************************************************************
** Description: Function uses a queue to simulate a buffer. User is first asked how many rounds
                they want the simulation to run, then they are asked for the percentage chance 
                that a number will be added to the back of the buffer each round, and then they
                are asked what percentage chance that a number will be removed from the front of
                the buffer each round. The simulation then runs and for each round it prints out 
                the current contents of the buffer, the length of the buffer, and the average
                length of the buffer as a double.
**************************************************************************************************/
void Simulation::buffer(){
    
    //uses a queue to create the buffer 
    std::queue<int, std::list<int>> myQueue; 
    
    int rounds = 0,             //user enters how many rounds they want
        N = 0,                  //stores the random number that may be added to buffer
        temp = 0,               //temporary storage
        endPercent = 0,         //percent chance a value will be added to buffer each round
        beginPercent = 0;       //percent chance a value will be removed from front each round
    double average = 0.0;       //stores the average length of buffer
     
    cout << "\nHow many rounds will be simulated? (min=1/max=100)" << endl;
    cout << "Selection: ";
    rounds = integerValidation(1, 100);

    cout << "\n\nWhat percent chance to put random number at end of buffer each round? (min=0/max=100)"
         << endl << "Selection: ";
    endPercent = integerValidation(0, 100);

    cout << "\n\nWhat percent chance to remove a number from the front of the buffer each round? (min=0/max=100)"
         << endl << "Selection: ";
    beginPercent = integerValidation(0, 100);
    
    //runs for the user specified number of rounds 
    for(int i = 1; i <= rounds; i++){ 
    
        N = this->randomInt(1000);          //random number between 1 and 1000 is stored

        temp = randomInt(100);              //random number between 1 and 100 is stroed
            
        //if the user's percent is greater than the temp variable, a number is added to the buffer 
        if(temp <= endPercent){
            myQueue.push(N);
        }

        temp = randomInt(100);              //random number between 1 and 100 is stored
         
        //if the user's percent is greater than the temp number, the front value is removed
        if(temp <= beginPercent && !myQueue.empty()){
            myQueue.pop();
        }
        
        cout << "\nValues in the buffer: ";

        //code block is used to pring the buffer contents 
        if(myQueue.empty()){
            cout << "***empty***" << endl;
        }
        else{
            this->printBuffer(myQueue);
        }

        cout << "Length of the buffer: " << myQueue.size() << endl;    
        
        //formula for average length of buffer was provided by instructor 
        average = (average * (i-1) + myQueue.size()) / i; 
        
        cout << "Average buffer length: " << std::showpoint << std::setprecision(3) 
             << std::fixed << average << endl; 
        
    } 
}

/**************************************************************************************************
** Description: Funtion is used to print the contents of the buffer. If the buffer is empty, there
                is nothing printed. This must be handled by the calling function. This function
                receives the queue (buffer) as an argument, so a copy of the queue is made when
                this function is called. This is done because in order to print the values in the
                queue, the values must be pop off the queue after printing so the next value can
                be printed. This prevents the original queue from being deleted.
**************************************************************************************************/
void Simulation::printBuffer(std::queue<int, std::list<int>> buffer){

    //prints out all the values in the buffer until there is nothing left in the buffer 
    while(!buffer.empty()){
     
        cout << buffer.front() << " ";
        buffer.pop();                       //removes front buffer value
    }
    cout << endl; 
}

/**************************************************************************************************
** Description: Function askes user to enter a string that they would like to be turned into a
                palindrome. User can eneter more than one word if they would like, the words just
                need to have a space between them. After the string is entered, the string is
                read into another string via stringstream. This is done one word at a time. The 
                current working work is push to the stack one character at a time, and then the
                word is concantenated with the characters in reverse order creating a palindrome.
                The palindromes are then printed to the console. 
**************************************************************************************************/
std::string Simulation::palindrome(){

    std::stack<char, std::vector<char>> myStack;        //stack for characters
    std::string word = "";                              //stores user's input
    std::string temp;           //temporary storage used to assist making palindrome
    std::string final;           //temporary storage used to assist making palindrome
    bool state = false; 

    cout << "\nEnter one or more words to turn into a palindrome(s)." << endl;
    cout << "\nWord: ";
    
    while(state == false){

        getline(std::cin, word);

        //loop checks all chars in string to ensure only alphabet letters are contained 
        for(int i = 0; i < word.length(); i++){
            if(!(isalpha(word.at(i))) && word.at(i) != ' '){
                cout << "\nERROR: Must only contain alphabet letters" << endl;
                cout << "Please enter a new string: ";
                i = word.length();
                state = false; 
            }
            else{
                state = true;
            }
        }
    }

    //used to process each word of user's input one at a time 
    std::istringstream iss(word);

    cout << "\nYour palindrome is ";
    
    while(iss >> temp){
        
        //block is used to push each letter of the curret word to the stack one at a time 
        for(int i = 0; i < temp.length(); i++){
            myStack.push(temp.at(i));
        }

        //block is used to add each letter from the stack to the current word in reverse order 
        while(!myStack.empty()){
            temp += myStack.top(); 
            myStack.pop();
        }
        //concantenates all palindromes together before printing
        final += temp + ' ';
    } 
    cout << final << endl; 
    
    return final; 
}

/**************************************************************************************************
** Description: Function takes in an integer as an argument for the max random value to return.
                The random number between 1 and the max value passed is generated and returned.
**************************************************************************************************/
int Simulation::randomInt(int max){

    return (rand() % max) + 1;
}
