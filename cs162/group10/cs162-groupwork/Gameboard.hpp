/*******************************************************************************
** Program Name: Group Project - Ant Massacre
** Author: Catrina Joos
** Date: 4/23/2019
** Description: Gameboard Header File
*******************************************************************************/

#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BugType.hpp"
#include "Point.hpp"
#include "Critter.hpp"

// for use throughout the game
//enum BugType {ANT,BUG,CRITTER,EMPTY};
class Gameboard {
	private:
		Critter*** board;
		int columns;
		int rows;
		std::vector<Critter*> antVector, babyAntVector; // points to the same bit of memory that's stored in the critter array
		std::vector<Critter*> bugVector, babyBugVector; // this is so we can loop through just the ants or just the bugs
		void setGrid(int,int); //verifies rows and columns values, sets to default 20 x 20 if invalid values
		void setMaxSteps(int);
		void initialize(int,int);
		void updateBoard();
		void actOnCritters(BugType,char);
		void breedCritter(Critter*);
		void moveCritter(Critter*);
		bool starveCritter(Critter*);
		void findAndRemoveFromVector(Critter*,Point);
		public:
			Gameboard();
			Gameboard(int,int);
			void printBoard();
			void playGame();
			void playGame(int);

			// functions to handle adding or removing critters to/from the board
			bool addCritter(Critter*);
			bool removeCritter(Point);

			// functions to be queried by Critters to find out about board state
			bool isValid(Point); // returns true if point is within the board
			bool isEmpty(Point); // returns true if point is valid and if pointer at y,x is null
			bool hasAnt(Point); // dependent on ant.getType() being ANT
			bool hasBug(Point);
			void cleanup(); // cleans up memory

};

#endif
