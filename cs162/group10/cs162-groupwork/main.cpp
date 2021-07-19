/*********************************************************************************************
* Program Name: Main.cpp
* Author: Group 10
* Date: 4/30/2019
* Description: This is the main for the predator prey game.
**********************************************************************************************/

#include "Gameboard.hpp"
#include "Menu.hpp"
#include "Interface.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
int main()
{
	std::srand(std::time(0));
	Menu menu = Menu();																		//Creating the menu object
	Interface interface = Interface();														//creating the interface object

	menu.displayInitialPrompts();															//prompt the user for initial values

	Gameboard gameboard = Gameboard(menu.getRowSize(), menu.getColumnSize());				//Create the gameboard
	Gameboard* ptrToGameboard = &gameboard;													//Get the pointer to the gameboard

	menu.addCritters(ptrToGameboard, interface);											//Add critters to the gameboard

	std::cout <<"\nInitial Board State\n\n";												//prints the initial board state
	ptrToGameboard->printBoard();

	for (int incrementer = 0; incrementer < menu.getStepSize(); incrementer++) {			//increments through the step size

		int stepNumber = incrementer + 1;
		ptrToGameboard->playGame(stepNumber);												//plays the game 1 turn for each step

		if (incrementer == menu.getStepSize() - 1) {										//if at the last step number
			menu.continuePrompt();															//ask user if they would like to continue
		}
	}

	ptrToGameboard->cleanup();																//free up the gameboard memory

	return 0;
}
