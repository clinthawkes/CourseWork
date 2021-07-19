/*********************************************************************************************
* Program Name: Main.cpp
* Author: Group 10
* Date: 4/30/2019
* Description: This is the prototype Main for predator prey.
**********************************************************************************************/

#include "Gameboard.hpp"
#include "Menu.hpp"
#include "Interface.hpp"
#include <iostream>
#include <string>

int main()
{
	std::string input;

	Menu menu = Menu();
	Interface interface = Interface();

	menu.displayInitialPrompts();

	Gameboard gameboard = Gameboard(menu.getRowSize(), menu.getColumnSize());
	Gameboard* ptrToGameboard = &gameboard;
	std::getline(std::cin, input);

	menu.addCritters(ptrToGameboard, interface);
	std::getline(std::cin, input);
	
	std::cout <<"\nInitial Board State\n\n";
	ptrToGameboard->printBoard();
	std::getline(std::cin, input);

	for (int incrementer = 0; incrementer < menu.getStepSize(); incrementer++) {
		
		int stepNumber = incrementer + 1;
		ptrToGameboard->playGame(stepNumber);

		if (incrementer == menu.getStepSize() - 1) {
			menu.continuePrompt();
		}
	}

	ptrToGameboard->cleanup();

	return 0;
}
