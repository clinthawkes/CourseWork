#include "SBoard.hpp"
#include <iostream>
 
using std::cout;
using std::cin;
using std::endl;

int main()
{
    SBoard game1;
    int squares = 0;
    
    //squares = game1.placeToken(4,4); 
    game1.readPlacementsFromFile("numbers.txt");
    //game1.readPlacementsFromFile("allnumbers.txt");
    //game1.printBoard();
    //for(int i = 0; i < 100000000; i++){ 
    //    squares = game1.placeToken(6,3);
    //    game1.removeToken(6,3);} 
    squares = game1.placeToken(6,3); 
    //squares = game1.placeToken(6,3); 
    //squares += game1.placeToken(3,7); 
    //squares = game1.placeToken(0,0); 
    //squares = game1.placeToken(0,0); 
    //squares = game1.placeToken(0,9); 
    //squares = game1.placeToken(9,0); 
    //squares = game1.placeToken(9,9); 
    //game1.printBoard();
    cout << "Number of squares completed is " << squares << endl; 
    cout << "Number of tokens is " << game1.getNumTokens() << endl;

    return 0;
}
    
