/**************************************************************************************************
** Program Name:Searching and Sortin
** Author:      Clinton Hawkes
** Date:        05/22/2019
** Description: This class is used to test the functionality of the search and sort functions
                found below. More details about each function can be found below.
**************************************************************************************************/

#include "Test.hpp"
#include "validation.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

//default constructor
Test::Test(){
}

/**************************************************************************************************
** Description: Function displays the available options and allows the user to choose one of them.
                After the user chooses an option and the input is validated, the user's choice
                is passed back to the calling function.
**************************************************************************************************/
int Test::menu(){

    int choice = 0;         //stores user's choice

    cout << "\n\n                    TESTING MENU                    " << endl;
    cout << "====================================================" << endl;
    cout << "\n*** Values already read from files." << endl;
    cout << "1. Simple search of files. " << endl;
    cout << "2. Sort the files. " << endl;
    cout << "3. Binary search sorted files.(must be sorted first)" << endl;
    cout << "4. Quit " << endl; 
    cout << "\nSelection: ";
    
    //validates user's input through the use of integerValidation function 
    choice = integerValidation(1,4);
    
    return choice;          //returns user's validated choice
}

/**************************************************************************************************
** Description: Function is used to control program flow by calling the appropriate functions
                and looping until the user chooses to quit the program. This function relies on 
                the menu function to determine which option the user wants to do. After the user
                makes a decision, the corresponding functions are called to perform the desired
                operations.
**************************************************************************************************/
void Test::run(){
    
    int option = 0; 
    int target = 0;
    bool state = true;
     
    //calls function to read integers from files before user interaction 
    this->readFiles();
    
    //runs until user chooses to quit 
    while(state){

        //gets user's choice from the menu 
        option = this->menu();

        switch(option){

            case 1: cout << "\nWhat is the target value? " << endl << "Target: ";
                    target = integerValidation(-10000, 10000);
                    
                    //following 4 lines will display if the target is found in each vector
                    cout << "\nnum.txt: " << this->simpleSearch(original, target) << endl;
                    cout << "\nearly.txt: " << this->simpleSearch(beginning, target) << endl;
                    cout << "\nmiddle.txt: " << this->simpleSearch(middle, target) << endl;
                    cout << "\nend.txt: " << this->simpleSearch(end, target) << endl;
                    break;
                    
            case 2: //if user chooses to sort, all 4 vectors will be sorted using the sort function 
                    cout << "\nSorting num.txt ..." << endl; 
                    this->sort(original);
                    cout << "\n\nSorting early.txt ..." << endl; 
                    this->sort(beginning);
                    cout << "\n\nSorting middle.txt ..." << endl; 
                    this->sort(middle);
                    cout << "\n\nSorting end.txt ..." << endl; 
                    this->sort(end);
                    break;
            
            case 3: cout << "\nWhat is the target value? " << endl << "Target: ";
                    target = integerValidation(-10000, 10000);
                    
                    //following 4 lines will display if the target is found in each file 
                    cout << "\nnum.txt: " << this->binarySearch(original, target) << endl;
                    cout << "\nearly.txt: " << this->binarySearch(beginning, target) << endl;
                    cout << "\nmiddle.txt: " << this->binarySearch(middle, target) << endl;
                    cout << "\nend.txt: " << this->binarySearch(end, target) << endl;
                    break;

            case 4: state = false;
                    break;
                    
        }
    }
}

/**************************************************************************************************
** Description: Function opens four files and reads their integers into a vector. The four files
                are chosen by the programmer and cannot be changed by the user.
**************************************************************************************************/
void Test::readFiles(){

    int temp = 0;               //temporary store for numbers being read from files 
    
    std::ifstream input;        //object used to read from files
    
    //opens the file and reads all the numbers into a vector
    input.open("num.txt");   

    while(input >> temp){

        original.push_back(temp);
    }

    input.close();              //closes file

    //opens the file and reads all the numbers into a vector
    input.open("early.txt");

    while(input >> temp){

        beginning.push_back(temp);
    }

    input.close();              //close file
    
    //opens the file and reads all the numbers into a vector
    input.open("middle.txt");
    
    while(input >> temp){

        middle.push_back(temp);
    }

    input.close();              //close file

    //opens the file and reads all the numbers into a vector
    input.open("end.txt");

    while(input >> temp){

        end.push_back(temp);
    }

    input.close();              //close file

}

/**************************************************************************************************
** Description: Function performs a linear search of a vector for a given target value. The vector
                and the target are passed as arguements. If the target value is found, a string
                confirming the target has been found is returned. If the target value is not found,
                a string stating that is returned.
**************************************************************************************************/
std::string Test::simpleSearch(std::vector<int> list, int value){

    std::string found = "target value found";
    std::string none = "target value not found"; 

    //loops through all the elements in the vector 
    for(int i = 0; i < list.size(); i++){

        if(list.at(i) == value){
            return found;           //message returned saying target is found
        }
    }
    return none;                    //message returned saying target not found
}

/**************************************************************************************************
** Description: Function is used to ask the user what they would like to call the output file for
                the sorted numbers, takes in the vector that needs to be sorted by reference, 
                sorts the vector in ascending order, writes all the numbers of the sorted vector
                to the output file and prints the numbers to the console.

                ***Code example found in the book
**************************************************************************************************/
void Test::sort(std::vector<int> &array){

    int temp = 0;
    bool swap;                  //swap indicator
    std::ofstream of;           //output stream object for writing to file
    std::string name = "";      //stores the name of the output file given by user

    cout << "Please enter a file name for the output file." << endl << "Filename: ";
    getline(cin, name);
     
    do{
        swap = false;           //swap indicator reset
        
        for(int i = 0; i < array.size()-1; i++){
            //current number in array is swapped with the next number if the next is smaller 
            if(array.at(i) > array.at(i+1)){
                //code for swapping the two values 
                temp = array.at(i);
                array.at(i) = array.at(i+1);
                array.at(i+1) = temp;
                swap = true;    //swap indicator confirms swap
            }
        }
    } while(swap);              //loops as long as one swap has been made during the for loop
   
    of.open(name);              //create and open file with user's desired name

    for(int a = 0; a < array.size(); a++){
        of << array.at(a) << " ";       //writes the current number in the vector to the output file
        cout << array.at(a) << " ";     //prints the current number to the console
         
    }
    of.close();                 //close the output file
}

/**************************************************************************************************
** Description: Function takes in a vector of integers and an integer that specifies a number that
                the function will search for. If the target numer is found, a string message is
                returned stating that. If the target number is not found, a string message is 
                returned stating that as well.

                ***Code example found in the book
**************************************************************************************************/
std::string Test::binarySearch(std::vector<int> list, int target){

    int first = 0,              //index of number beginning search range
        last = list.size()-1,   //index of number ending search range
        middle;                 //index of number in middle of first and last
    bool found = false;
    std::string present = "target value found";
    std::string none = "target value not found"; 

    //loop runs until the target is found or there are no more numbers to test  
    while(!found && first<=last){
        
        middle = (first + last)/2;

        //message confirming number found returned if the number being tested equals the target 
        if(list.at(middle) == target){
            return present;
        }
        //if the number being tested is greater than the target, the last index is one less than middle 
        else if(list.at(middle) > target){
            last = middle - 1;
        } 
        //if the number being tested is less than the target, the first index is one more than middle 
        else{
            first = middle + 1;
        }
    }
    //message stating the target was not found is returned if the loop runs long enough to terminate
    return none;
}
