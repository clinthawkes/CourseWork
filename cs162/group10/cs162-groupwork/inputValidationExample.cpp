/***************************************************************************
 * Program Name: Game.cpp
 * Author: Brian Yi
 * Date: 4/20/2019
 * Description: Input validation example taken from War Game.
 * **************************************************************************/	


#include <iostream>
#include <string>


//Constructor

Game::Game() {
	this->startOption = -1;		//Holds the start option value
	this->startOptionLB = 1;	//Holds the start option lower bound
	this->startOptionHB = 2;	//The start option higher bound
	this->numRounds = -1;		//The number of rounds
	this->numRoundsLB = 1;		//The lower bound of the number of rounds
	this->numRoundsHB = 100;	//The higher bound of the number of rounds
	this->dieTypeP1 = -1;		//The die type of player 1
	this->dieTypeP2 = -1;		//The die type of player 2
	this->dieTypeLB = 1;		//The lower bound of the die type menu option
	this->dieTypeHB = 2;		//The higher bound of the die type menu option
	this->dieSidesP1 = -1;		//The number of sides of player 1's die
	this->dieSidesP2 = -1;		//The number of sides of player 2's die
	this->dieSidesLB = 2;		//The lower bound of the allowed number of sides
	this->dieSidesHB = 1000;	//The higher bound of the allowerd number of sides
	this->pointTotalP1 = 0;		//Holds the point total of player one
	this->pointTotalP2 = 0;		//Holds the point total of player two
}

void Game::displayGameOptions() {
	std::string userInput;
	
	std::cout << "\nHow many rounds would you like to play ?\n";
	std::cout << "Select a number from 1 to 100\n\n";

	std::getline(std::cin, userInput);

	while (!intCheck(userInput, this->numRoundsLB, this->numRoundsHB)) {	//Checks if input is an int between
		std::cout << "\nInvalid value, please try again\n\n";		//numRoundsLB and numRoundsHB
		std::getline(std::cin, userInput);				//The same structure is used below for
	}									//The rest of the prompts

	this->numRounds = std::stoi(userInput);

	std::cout << "\nWhat type of die would Player 1 like ?\n";
	std::cout << "1. Normal Die\n2. Loaded Die\n\n";

	std::getline(std::cin, userInput);

	while (!intCheck(userInput, this->dieTypeLB, this->dieTypeHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, userInput);
	}
	
	this->dieTypeP1 = std::stoi(userInput);

	std::cout << "\nWhat type of die would Player 2 like ?\n";
	std::cout << "1. Normal Die\n2. Loaded Die\n\n";

	std::getline(std::cin, userInput);

	while (!intCheck(userInput, this->dieTypeLB, this->dieTypeHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, userInput);
	}
	
	this->dieTypeP2 = std::stoi(userInput);

	std::cout << "\nHow many sides would Player 1 like on the die ?\n";
	std::cout << "Pick a number from 2 to 1000\n\n";

	std::getline(std::cin, userInput);

	while (!intCheck(userInput, this->dieSidesLB, this->dieSidesHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, userInput);
	}
	
	this->dieSidesP1 = std::stoi(userInput);

	std::cout << "\nHow many sides would Player 2 like on the die ?\n";
	std::cout << "Pick a number from 2 to 1000\n\n";

	std::getline(std::cin, userInput);

	while (!intCheck(userInput, this->dieSidesLB, this->dieSidesHB)) {
		std::cout << "\nInvalid value, please try again\n\n";
		std::getline(std::cin, userInput);
	}
	
	this->dieSidesP2 = std::stoi(userInput);
	
	std::cout << "\n\n";
}


//This function checks if a user input is an integer at or between the bound values.
//This function takes the user input as a string, the lower bound as an int and the
//higher bound as an int. The function returns a False if it fails the checks and a 
//True if it passes the checks. If it passes the checks then the string can be a valid
//int value.

bool Game::intCheck(std::string inputValue, int lowerBound, int higherBound) {
	
	if (inputValue == "") {		//If there is no input. if there is no input
		return false;		//false is returned.
	}
	
	int stringLength = inputValue.length(); 				//Getting the length of the string

	for(int incrementer = 0; incrementer < stringLength; incrementer++) {	//If any element of the string is not a digit (0 - 9)
		if (!(std::isdigit(inputValue[incrementer]))) {			//return false.
			return false;
		}
	}

	int checkValue = std::stoi(inputValue);					//casting the string to int

	if ((checkValue <= higherBound) && (checkValue >= lowerBound)) {	//If the int is between or equal to the bound values
		return true;							//true is returned. All the ckecks have been satisfied.
	}

	return false;								//false is returned if this check does not pass.
}
