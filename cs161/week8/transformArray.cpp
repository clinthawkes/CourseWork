/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/24/2019
** Description: 
*******************************************************************************/
/*
#include <iostream>

using std::cout;
using std::endl;

void transformArray(int*&, int);

int main(){

    int* myArray = new int[8];
    myArray[0] = 4;
    myArray[1] = 2;
    myArray[2] = 5;
    myArray[3] = 1;
    myArray[4] = 7;
    myArray[5] = 5;
    myArray[6] = 9;
    myArray[7] = 10;
    
    cout << "address of myArray is " << myArray << endl; 
    transformArray(myArray, 8);
    cout << "address of myArray is " << myArray << endl; 

    for(int i = 0; i < 16; i++)
        cout << myArray[i] << endl;
    
    delete [] myArray;
    myArray = nullptr;

    return 0;
}
*/
/*******************************************************************************
** Description: Takes in a pointer by reference that is pointing to a dynamic
                array of ints. The function creates a new dynamic array of ints
                that is twice the size of the input array. A copy of the 
                ints from the input array are copied to the new array, and then 
                a copy of the ints*2 from the input array are copied to the new
                array. The original input array is deleted, the address of the 
                newArray pointer is assigned to the input array pointer, and the 
                newArray pointer is then assigned a NULL value.
*******************************************************************************/

void transformArray(int* &inArray, int size){
    //creates a new pointer that points to a dynamic array of ints 
    int* newArray = new int[size*2];
    
    //copies ints from input array to the newArray 
    for(int i = 0; i < size; i++)
        newArray[i] = inArray[i];
    //copies ints*2 from input array to the newArray
    for(int x = 0; x < size; x++)
        newArray[x+size] = inArray[x]*2;
    
    //deletes the input array that is no longer needed 
    delete [] inArray;
    //assigns the memory address of newArray pointer to the input array pointer 
    inArray = newArray;
    //memory address of newArray is replaced with NULL  
    newArray = nullptr;
}


