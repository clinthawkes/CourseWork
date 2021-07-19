/*********************************************************************************
* Program Name: Menu.cpp
* Author: Brian Yi
* Date: 4/29/2019
* Description: This is the Menu class for the predator prey game.
*				It prompts the user and includes input validation.
*********************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include "Menu.hpp"
#include "Point.hpp"
#include "Gameboard.hpp"
#include "Interface.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"

//The default constructor

Menu::Menu() {
	this->columnSizeLB = 5;
	this->columnSizeHB = 100;
	this->rowSizeLB = 5;
	this->rowSizeHB = 100;
	this->stepSizeLB = 1;
	this->stepSizeHB = 500;
	this->antNumLB;
	this->antNumHB;
	this->doodlebugNumLB;
	this->doodlebugNumHB;

	this->availableBoardPositions;
	this->columnSize;
	this->rowSize;
	this->stepSize;

}


//Displays the initial prompts for game creation

void Menu::displayInitialPrompts() {
	std::string inputValue;

	std::cout << "\nWelcome to the predator prey game: EC edition\n\n";

	std::cout << "\nPlease enter the number of rows from " << this->rowSizeLB << " to " << this->rowSizeHB << "\n\n";				//gets the number of rows from user
	std::getline(std::cin, inputValue);

	while (!this->intCheck(inputValue, rowSizeLB, rowSizeHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, inputValue);
	}

	this->rowSize = std::stoi(inputValue);

	std::cout << "\nPlease enter the number of columns from " << this->columnSizeLB << " to " << this->columnSizeHB << "\n\n";		//gets the number of columns from user
	std::getline(std::cin, inputValue);

	while (!this->intCheck(inputValue, columnSizeLB, columnSizeHB)) {																	
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, inputValue);
	}

	this->columnSize = std::stoi(inputValue);

	this->createAvailableBoardPositions();																							//creates the number of possible board positions

	std::cout << "\nPlease enter the number of steps from " << this->stepSizeLB << " to " << this->stepSizeHB << "\n\n";			//gets the step size from user
	std::getline(std::cin, inputValue);

	while (!this->intCheck(inputValue, stepSizeLB, stepSizeHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, inputValue);
	}

	this->stepSize = std::stoi(inputValue);
	
	this->createAntBounds();																										//Create the higher and lower bound for the num of ants

	std::cout << "\nPlease enter the number of ants from " << this->antNumLB << " to " << this->antNumHB << "\n\n";
	std::getline(std::cin, inputValue);

	while (!this->intCheck(inputValue, antNumLB, antNumHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, inputValue);
	}

	this->antNum = std::stoi(inputValue);

	this->createDoodlebugBounds();																									//Create the higher and lower bounds for the num of doodlebugs

	std::cout << "\nPlease enter the number of doodlebugs from " << this->doodlebugNumLB << " to " << this->doodlebugNumHB << "\n\n";
	std::getline(std::cin, inputValue);

	while (!this->intCheck(inputValue, doodlebugNumLB, doodlebugNumHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, inputValue);
	}
	
	this->doodlebugNum = std::stoi(inputValue);
}

//Gets the row size

int Menu::getRowSize() {
	return this->rowSize;
}

//Gets the column size

int Menu::getColumnSize() {
	return this->columnSize;
}

//Gets the step size

int Menu::getStepSize() {
	return this->stepSize;
}

//Creates and sets the min and max bound of ants

void Menu::createAntBounds() {
	this->antNumLB = 0;
	this->antNumHB = this->availableBoardPositions;
}

//Creates and sets the min and max bound of doodlebugs

void Menu::createDoodlebugBounds() {
	this->doodlebugNumLB = 0;
	this->doodlebugNumHB = this->availableBoardPositions - this->antNum;
}

//Creates the number of available spaces for bugs
//Sets available board positions

void Menu::createAvailableBoardPositions() {
	this->availableBoardPositions = this->columnSize * this->rowSize;
}


//Adds ants and doodlebugs to the game board
//Takes a pointer to the game board and takes an interface obeject by reference

void Menu::addCritters(Gameboard* gameboard, Interface &interface) {
	std::vector<Point> availablePoints;
	std::srand(std::time(nullptr));
	int vectorIndex;
	Point critterLocation;

	for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {											//creates a vector of all possible board positions by iterating over the row and column
		for (int columnIndex = 0; columnIndex < this->columnSize; columnIndex++) {							//For each row, get all column values
			availablePoints.push_back(Point(rowIndex, columnIndex));
		}
	}

	for (int antNum = 0; antNum < this->antNum; antNum++) {													//for all ants
		vectorIndex = std::rand() % availablePoints.size();													//get a random vector point index
		critterLocation = availablePoints[vectorIndex];														//get the vector location value
		if (gameboard->addCritter(interface.createAnt(critterLocation, gameboard))) {						//creates the critter in the interface object and adds to the gameboard
			availablePoints.erase(availablePoints.begin() + vectorIndex);									//erase the vector point element
		}
		else {
			std::cout << "\nAnt addition error in Menu/Gameboard\n\n";
		}
	
	}

	for (int doodlebugNum = 0; doodlebugNum < this->doodlebugNum; doodlebugNum++) {							//for all doodlebugs
		vectorIndex = std::rand() % availablePoints.size();													//get a random vector point index
		critterLocation = availablePoints[vectorIndex];														//get the vector location value
		if (gameboard->addCritter(interface.createDoodlebug(critterLocation, gameboard))) {					//creates the critter in the interface object and adds to the gameboard
			availablePoints.erase(availablePoints.begin() + vectorIndex);									//erase the vector point element
		}
		else {
			std::cout << "\nDoodlebug addition error in Menu/Gameboard\n\n";
		}
	}
}


//Prompts the user to continue or quit

void Menu::continuePrompt() {
	std::string userInput;
	int continuePromptLB = 1;
	int continuePromptHB = 2;
	int continuePrompt;
	int newStepSizeLB;
	int newStepSizeHB;
	int stepSizeAddition;

	if (this->stepSize == stepSizeHB) {																	//check if max step size is reached
		std::cout << "\nGame over, reached max step size of " << stepSizeHB << "\n\n";
	}
	else {
		std::cout << "\nWould you like to continue playing ?";											// prompt the user to continue playing
		std::cout << "\n1. Continue";
		std::cout << "\n2. Quit\n\n";
		std::getline(std::cin, userInput);

		while(!this->intCheck(userInput, continuePromptLB, continuePromptHB)) {						
			std::cout << "\nInvalid value, please try again\n\n";
			std::getline(std::cin, userInput);
		}

		continuePrompt = std::stoi(userInput);
		if (continuePrompt == 1) {
			newStepSizeLB = 1;
			newStepSizeHB = this->stepSizeHB - this->stepSize;											//create the number of steps to the higher bound

			std::cout << "\nPlease enter the number of steps from " << newStepSizeLB << " to " << newStepSizeHB << "\n\n";
			std::getline(std::cin, userInput);

			while(!this->intCheck(userInput, newStepSizeLB, newStepSizeHB)) {
				std::cout << "\nInvalid value, please try again\n\n";
				std::getline(std::cin, userInput);
			}

			stepSizeAddition = std::stoi(userInput);

			this->stepSize += stepSizeAddition;															//adds the number of steps to the step size
		}
		else {
			std::cout << "\nGame over, thanks for playing\n\n";
		}
	}
}

//This function checks if a user input is an integer at or between the bound values.
//This function takes the user input as a string, the lower bound as an int and the
//higher bound as an int. The function returns a False if it fails the checks and a 
//True if it passes the checks. If it passes the checks then the string can be a valid
//int value.

bool Menu::intCheck(std::string inputValue, int lowerBound, int higherBound) {

	if (inputValue == "") {																			//If there is no input. if there is no input
		return false;																				//false is returned.
	}

	int stringLength = inputValue.length(); 														//Getting the length of the string

	for (int incrementer = 0; incrementer < stringLength; incrementer++) {							//If any element of the string is not a digit (0 - 9)
		if (!(std::isdigit(inputValue[incrementer]))) {												//return false.
			return false;
		}
	}

	int checkValue = std::stoi(inputValue);															//casting the string to int

	if ((checkValue <= higherBound) && (checkValue >= lowerBound)) {								//If the int is between or equal to the bound values
		return true;																				//true is returned. All the ckecks have been satisfied.
	}

	return false;																					//false is returned if this check does not pass.
}
