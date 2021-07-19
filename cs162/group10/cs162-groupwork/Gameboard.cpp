/*******************************************************************************
** Program Name: Group Project - Group Project
** Author: Catrina Joos
** Date: 4/23/2019
** Description: Gameboard Source File
*******************************************************************************/

#include "Gameboard.hpp"
//#include <iostream>
//using std::cin;

// constructor
Gameboard::Gameboard(){
	initialize(20,20);
}

// constructor
Gameboard::Gameboard(int r,int c){
	initialize(r,c);
}


// initalizes starting board state - a r x c 2d array of null critter pointers
void Gameboard::initialize(int r,int c){
	setGrid(r,c); // makes sure that row and column values are valid - sets to default values if not

	//make the pointer array
	board = new Critter**[this->rows];

	// create n rows of critter pointer arrays
	for(int i=0;i<this->rows;i++){
		board[i] = new Critter*[this->columns];

		//for each slot in that Critter array, start with a null pointer
        	for(int j = 0; j < this->columns; j++){
	            board[i][j] = nullptr;
        	}
	}
}

// Prints the gameboard
void Gameboard::printBoard(){

	// loop through the array and see what's in it
	for(int i=0;i<this->rows;i++){
		std::cout<<"|";
		for(int j=0;j<this->columns;j++){
			Point p(i,j);
			// if it's empty, print whitespace
			if(this->isEmpty(p)){
				std::cout<<std::setw(4)<<"|";
			}
			else if(this->hasAnt(p)){		// if it has an ant, print o
				std::cout << " O |";
			}
			else if(this->hasBug(p)){		// if it has a bug, print X
				std::cout << " X |";
			}
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

// plays one rount of the game
void Gameboard::playGame(int stepNumber){


	// print out current step number
	std::cout << "Current Step: "<< stepNumber << std::endl;
	this->actOnCritters(BUG,'m'); // move the bugs
	
	this->actOnCritters(ANT,'m'); // move the ants
	this->actOnCritters(BUG,'b'); // breed the bugs
	this->actOnCritters(ANT,'b'); // breed the ants
	this->actOnCritters(BUG,'s'); // starve the bugs
	this->printBoard(); // print the new board

}

// Tells the critters want to do based upon the flag that was passed in
void Gameboard::actOnCritters(BugType type, char flag){
	if(type == ANT){
		for(unsigned int i=0;i<antVector.size();i++){		// for each Ant in the ant vector
			//std::cout<<"i is "<< i <<" flag "<<flag<<std::endl;
			if(flag =='m'){
				this->moveCritter(antVector[i]); // move the ant
			}
			if(flag == 'b'){
				this->breedCritter(antVector[i]); // reed the ant
			}
		}
	}
	if(type == BUG){
		for(unsigned int i = 0;i<bugVector.size();i++){		// for each bug in the bug vector
			if(flag == 'm'){
				this->moveCritter(bugVector[i]);	// move the bug
			}
			if (flag == 'b'){
				this->breedCritter(bugVector[i]);	// breed the bug
			}
			if( flag == 's'){
				if(this->starveCritter(bugVector[i]))	//if the bug starved, it's been removed from the vector
				{					// decrement i so we don't skip a bug that's moved into dead bug's former place
		                    i--;
                		} 
			}
		}
	}
}

// tells the bug to try to starve -- return value is true if the critter starves, false if it did not qualify starve
// Critter will remove itself from the board
bool Gameboard::starveCritter(Critter* critter){
	return critter->starve();
}

// moves the critter
void Gameboard::moveCritter(Critter* critter){
	// checks for a null pointer, unikely but better safe than sorry
	if(critter != nullptr){
		Point p = critter->move();	// tell the critter to move
		if(this->isValid(p)){		// if the point is a valid move, update the references in the game board
			int row = p.getY();
			int col = p.getX();
			board[row][col] = critter;

			// remove the reference to the critter at the spot that it moved from
			Point oldP = critter->getOldLocation();
			row = oldP.getY();
			col = oldP.getX();

			// critter has moved, so it's now a null pointer
			board[row][col] = nullptr;
		}
	}
}

// Tells the critter to breed, if the 
void Gameboard::breedCritter(Critter* critter){
	Critter* baby = critter->breed();
	if (baby != nullptr){
//		Point p = baby->getCurrentLocation();
		//std::cout<<"Baby at row "<<p.getY()<<" col "<<p.getX()<<std::endl;
		this->addCritter(baby);
	}
}

// cleanup memory at the end of the game
void Gameboard::cleanup(){
	for(int i = 0; i<this->rows; i++){
		for(int j=0;j<this->columns;j++){
			if (board[i][j] != nullptr){ // if this is not a null pointer, then there's something here we need to delete
				delete board[i][j];
			}
		}
		delete[] board[i]; // delete the 1D array
	}
	delete[] board; // delete the board
	antVector.clear(); // clear the vectors
	bugVector.clear();
}

// Adds a critter to the gameboard. Returns true to indicate success, false to indicate failure
bool Gameboard::addCritter(Critter* ptr){
	Point p = ptr->getCurrentLocation(); // get the critter's current location
	if(this->isEmpty(p)){		// isEmpty() only returns true if the point is valid and if it's empty
		int row = p.getY();	// update the board
		int column = p.getX();
		board[row][column] = ptr;

		// add the critter to the appropriate vector
		if(ptr->getType() == ANT){
			antVector.push_back(ptr);
		}
		if(ptr->getType() == BUG){
			bugVector.push_back(ptr);
		}
		return true; // return true -- critter successfully added
	}
	return false; // false -- critter was not added

}

// removes a critter from point p
bool Gameboard::removeCritter(Point p){
	int row = p.getY();
	int column = p.getX();
	if(!this->isEmpty(p)){	// make sure that the point is occupied before trying to remove it
		this->findAndRemoveFromVector(board[row][column],p); 	// to avoid dangling pointers,
									//  we need to remove the pointer from the vector before deleting
		delete board[row][column];	// delete the critter
		board[row][column] = nullptr;	// reassign to null pointer
		return true;	// true - we removed the critter
	}
	return false;  // false - no critter was removed
}

// Removes a critter from the appropriate vector
void Gameboard::findAndRemoveFromVector(Critter* critter, Point p1){
	if(critter->getType() == BUG){
		bool bugFound = false;
		unsigned int i = 0;
		while(!bugFound && i < bugVector.size()){	// go through the bugs in the vector until you find the one at point p -- that's the one we want to remove
			Point p2=bugVector[i]->getCurrentLocation();
			if(p2.isEqual(p1)){
				bugVector.erase(bugVector.begin()+i);	// remove the bug from this vector
				bugFound = true; 			// indicate that we found the bug so we can quit the looop
			}
			i++;
		}
	}
	// if the critter is an Ant
	if(critter->getType() == ANT){
		bool antFound = false;
		unsigned int i=0;
		// loop through until you find the pointer to this ant in the vector and remove it
		while(!antFound && i<antVector.size()){
			Point p2 = antVector[i]->getCurrentLocation();
			if(p2.isEqual(p1)){
				antVector.erase(antVector.begin()+i);	// remove the ant pointer from the vector
				antFound = true;			// update the boolean so we can quit the loop
			}
			i++;
		}
	}
}


// returns true if the point is within the limits of the board
bool Gameboard::isValid(Point p){

	// rows and column values cannot be negative
	if(p.getY()<0){
		return false;
	}
	// outside of the array - invalid point
	if(p.getX()<0){
		return false;
	}

	// row and column values cannot be greater than the number of rows/column
	if(p.getY()>=this->rows){
		return false;
	}
	if(p.getX()>=this->columns){
		return false;
	}
	return true;
}

// returns true if point p is a valid point and it's a nullptr
bool Gameboard::isEmpty(Point p){
	// check to see if it's a valid move
	if(this->isValid(p)){
		// only return true if this point is valid and current pointer points to null
		if(board[p.getY()][p.getX()] == nullptr){
			return true;
		}
	}
	return false;
}

// returns true if point is valid and if object at point P is a BugType of ANT
bool Gameboard::hasAnt(Point p){
	// empty square
	if(this->isEmpty(p)){
		return false;
	}
	// outside of array - invalid
	if(!this->isValid(p)){
		return false;
	}
	// there is an ant here
	if(board[p.getY()][p.getX()]->getType() == ANT){
		return true;
	}
	// probably a bug
	return false;
}

// returns true if point is valid and BUG located at Point p
bool Gameboard::hasBug(Point p){
	// empty square
	if(this->isEmpty(p)){
		return false;
	}
	// invalid square -- outside of array
	if(!this->isValid(p)){
		return false;
	}
	// there is a bug here
	if(board[p.getY()][p.getX()]->getType() == BUG){
		return true;
	}
	// probably an ant
	return false;
}


// verifies that the board is at least a minimum size of 5 x 5
// input validation takes care of making sure min/max sizes are obeyed...but just in case 
void Gameboard::setGrid(int r, int c){

	// rows values are valid
	if(r>=5){
		this->rows = r;
	}
	// assign the default
	else{
		this->rows = 5;
	}
	// column values are valid
	if(c>=5){
		this->columns = c;
	}
	// assign the default
	else{
		this->columns = 5;
	}
}

