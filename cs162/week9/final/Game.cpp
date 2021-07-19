/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/06/2019
** Description: Implementation file for the Game class. The Game class is responsible for 
                creating the six different rooms and linking them together, creating the Player
                object, and finally making all the function calls needed to make the game run
                smoothly. Details of the member functions can be found below
**************************************************************************************************/

#include "Game.hpp"
#include "menu.hpp"
#include "Ladder.hpp"
#include "Tools.hpp"
#include "Chemical.hpp"
#include "Gear.hpp"
#include "Workbench.hpp"
#include "Parts.hpp"
#include <iostream>

//default constructor for the Game class
Game::Game(){
    
    ladder = new Ladder;            //creates the Ladder room
    tools = new Tools;              //creates the Tools room
    chemical = new Chemical;        //creates the Chemical room
    gear = new Gear;                //creates the Gear room
    workbench = new Workbench;      //creates the Workbench
    parts = new Parts;              //creates the Parts room

    //the following block links all the rooms to one another so the player can move about the game
    //it was much easier to hard code the connections in the correct pattern
    ladder->setWest(tools);
    ladder->setSouth(parts);
    tools->setEast(ladder);
    tools->setSouth(workbench);
    tools->setWest(chemical);
    chemical->setEast(tools);
    chemical->setSouth(gear);
    gear->setNorth(chemical);
    gear->setEast(workbench);
    workbench->setWest(gear);
    workbench->setNorth(tools);
    workbench->setEast(parts);
    parts->setWest(workbench);
    parts->setNorth(ladder);
    
    //initial player location is set to the Ladder room 
    player.setLocation(ladder); 
        
}

//default deconstructor
Game::~Game(){
    
    //following block deletes all the rooms that were created by the constructor. This will prevent
    //any memory leaks
    delete ladder;                  
    ladder = nullptr; 
    delete tools;
    tools = nullptr; 
    delete chemical;
    chemical = nullptr; 
    delete gear;
    gear = nullptr; 
    delete workbench;
    workbench = nullptr; 
    delete parts;
    parts = nullptr; 
    

}

/**************************************************************************************************
** Description: Function is used to control the game flow. After the user chooses to play the game
                using the start menu, the game enters a loop of calling the user interaction menu, 
                getting the user's input, calling the function that will perform the action 
                requeested, and then repeat until there are no more steps remaining or the user
                wins.
**************************************************************************************************/
void Game::run(){

    bool state = true;              //controls the game loop 
    bool win = false;               //tracks whether the user wins or loses
    int select = 0; 
    int round = player.getMoveCount();      //sets the round counter
    
    state = startMenu();            //asks user to play or quit
    
    //game terminates if user quits 
    if(state == false){
        std::cout << "\nPlease play again soon!" << std::endl; 
        return;
    }

    //prints the initial map 
    player.getLocation()->showMap(round);
        
    while(state == true){
        
        //user chooses an action to perform in the room 
        select = menu();

        switch(select){

            //user chooses to investigate the room. (interact with structures) 
            case 1: state = player.getLocation()->investigate(player.getBackpack());
                    //if the hatch is blown open, the user wins and false is returned 
                    if(state == false){
                        win = true;
                    }                        
                    break;
                    
            //user chooses to move to a different room 
            case 2: player.setLocation(player.getLocation()->move());
                    player.decMoveCount();          //each move decreases remaining available moves
                    round = player.getMoveCount();
                    player.getLocation()->showMap(round);   //new map location is printed
                    break;
                    
            //user chooses to view what is in the player backpack        
            case 3: player.showBackpack();
                    break;

        }
        //if user runs out of moves, they lose the game 
        if(round < 0){
            state = false;
        }            
    }
    if(win == true){
        std::cout << "\n*************************************************************" << std::endl;
        std::cout << "         You escaped from the bunker just in time!!!!!" << std::endl;
        std::cout << "                         You WIN the game" << std::endl;
    }
    else{
        std::cout << "\nSorry, you ran out of time and died of dehydration." << std::endl;
        std::cout << "            Better luck next time..." << std::endl; 
    } 
}
