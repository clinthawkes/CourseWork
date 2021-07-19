/*********************************************************************************
* Program Name: Menu.hpp
* Author: Brian Yi
* Date: 4/29/2019
* Description: This is the Menu class for the predator prey game.
*				It prompts the user and includes input validation.
*********************************************************************************/


#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include "Gameboard.hpp"
#include "Interface.hpp"

class Menu {
private:
	bool endProgramFlag;
	int columnSizeLB;
	int rowSizeLB;
	int columnSizeHB;
	int rowSizeHB;
	int stepSizeLB;
	int stepSizeHB;
	int antNumLB;
	int doodlebugNumLB;
	int antNumHB;
	int doodlebugNumHB;
	
	int availableBoardPositions;
	int columnSize;
	int rowSize;
	int stepSize;
	int antNum;
	int doodlebugNum;

public:
	Menu();
	void displayInitialPrompts();
	int getRowSize();
	int getColumnSize();
	int getStepSize();
	void createAntBounds();
	void createDoodlebugBounds();
	void createAvailableBoardPositions();
	void addCritters(Gameboard *gameboard, Interface &interface);
	bool intCheck(std::string, int, int);
	void continuePrompt();
};

#endif
