/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/22/2019
** Description: Implementation file for the Game class. The Game class handles all the object
                creations and function calls for the testing of the characters. Information
                about the Menu functions can be found below.
**************************************************************************************************/

#include "Lineup.hpp"
#include "Losers.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Character.hpp"
#include "validation.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "Medusa.hpp"
#include "BlueMen.hpp"
#include "HarryPotter.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

//default constructor
Game::Game(){
}

/**************************************************************************************************
** Description: Function is the "traffic controller" of the program. This function is called by 
                from the main function after the rand() is seeded so the main does not have to 
                handle any logic. This function first creates the queue and stack objects to hold
                the fighters, asks the user how many fighters they want on each team, allows the
                user to choose the type of fighters and give each one a name, and then pairs up
                the fighters from each team to battle to the death. The losers from each team are
                put into one stack and the tournament will continue until one team loses all of
                it's fighters. The results of the tournament are then displayed and the winner is
                announced. User then has the option to view the list of losers and chooses the 
                option to play again or quit.
**************************************************************************************************/
void Game::play(){

    Lineup team1;                   //queue for team 1 fighters
    Lineup team2;                   //queue for team 2 fighters
    Losers graves;                  //stack for losing fighters
    Menu menu;                      //object for calling menu
    int choice = 0;
    bool state = true; 
    
    //user decides to play or quit 
    state = menu.startMenu();

    //loop will run until user chooses to quit 
    while(state == true){

        int match = 0;              //match counter
        int team1Points = 0;        //stores points earned by team 1    
        int team2Points = 0;        //stores points earned by team 2
    
        cout << "\nHow many players would you like on each team? (min=1/max=50)" << endl;
        cout << "Quantity: ";
        choice = integerValidation(1, 50);

        //populates team 1's lineup with the user specified number of players 
        for(int i = 0; i < choice; i++){
            //menu is called to allow user to choose type of player and give a name 
            team1.addBack(menu.menu1((i+1), choice));
        }
            
        //populates team 2's lineup with the user specified number of players 
        for(int i = 0; i < choice; i++){
            //menu is called to allow user to choose type of player and give a name 
            team2.addBack(menu.menu2((i+1), choice));
        }
        
        //tournament will run until one team has no more players remaining in lineup 
        while(!team1.isEmpty() && !team2.isEmpty()){

            int result = 0;         //stores which team won after each battle
            
            match++;

            //test function from project 3 is called to simulate battle between players 
            result = this->test(team1.getFront(), team2.getFront(), match);
            
            switch(result){

                //if team 1 won the current battle, this runs 
                case 1: graves.newHead(team2.getFront());   //team 2 player moved to loser stack
                        team2.removeFront();                //team 2 lineup reduced by one
                        team1.headNext();                   //team 1 player moved to back of lineup
                        team1Points += 2;                   //team 1 gets 2 points
                        team2Points--;                      //team 2 loses 1 point
                        break;

                //if team 2 won the current battel, this runs 
                case 2: graves.newHead(team1.getFront());   //team 1 player moved to loser stack
                        team1.removeFront();                //team 1 lineup reduced by one
                        team2.headNext();                   //team 2 player moved to back of lineup
                        team2Points += 2;                   //team 2 gets 2 points
                        team1Points--;                      //team 1 loses 1 point
                        break;
            }
        }
    
        //following output announces who wins and what the points are 
        cout << "\n______________________________________________" << endl;
        if(team1Points > team2Points){
            cout << "Winner of the tournament is Team 1" << endl;
            cout << "Team 1 points: " << team1Points << endl;
            cout << "Team 2 points: " << team2Points << endl;
        }
        else if(team1Points < team2Points){
            cout << "Winner of the tournament is Team 2" << endl;
            cout << "Team 1 points: " << team1Points << endl;
            cout << "Team 2 points: " << team2Points << endl;
        }
        else{
            cout << "Winner of the tournament... its a TIE" << endl;
            cout << "Team 1 points: " << team1Points << endl;
            cout << "Team 2 points: " << team2Points << endl;
        }

        cout << "\nWould you like a list of the losers? (1=yes/2=no)" << endl;
        cout << "Selection: ";
        choice = integerValidation(1,2);

        //lists the stack of losers if user chooses to do so 
        if(choice == 1){
            graves.traverse();
        }
        
        //determines if user wants to play again or quit 
        state = menu.endMenu();
         
        //next 3 lines clears the lineup queues and loser stack 
        team1.~Lineup(); 
        team2.~Lineup(); 
        graves.~Losers();

    } 
}

/**************************************************************************************************
** Description: This function is the brains battle. It is responsible for creating battle loops, 
                calling the various functions for the characters and displaying all the information 
                to the user for testing purposes.
**************************************************************************************************/
int Game::test(Character* first, Character* second, int round){
    
    Character* p1 = first;          //pointer to player 1 object
    Character* p2 = second;         //pointer to player 2 object
    Character* winner = nullptr;    //pointer to the winner of the battle

    bool battle = true; 
    int rnd = 1,                //round counter
        p1Roll = 0,             //holds attack and inflicted damage values for player 1
        p2Roll = 0;             //holds attack and inflicted damage values for player 2
    int victor = 0;             //holds the victors type variable
          

    while(battle == true){
                  
        //if round number is even 
        if(rnd%2 == 1){ 
            
            //player 1 attack function returns an attack value to be passes to player 2 defense 
            p1Roll = p1->attack();
            
            //player 2 defense function returns the actual inflicted damage value 
            p2Roll = p2->defense(p1Roll);
            
            //if the defender has sp of 0 or less, the defender loses 
            if(p2->getSP() <= 0){
                winner = p1; 
                victor = 1; 
                battle = false; 
            }
            rnd++;
        }
        else {
            
            //player 2 attack function returns an attack value to be passes to player 1 defense 
            p2Roll = p2->attack();
            
            //player 1 defense function returns the actual inflicted damage value 
            p1Roll = p1->defense(p2Roll);
            
            //if the defender has sp of 0 or less, the defender loses 
            if(p1->getSP() <= 0){
                winner = p2; 
                victor = 2; 
                battle = false; 
            }
            rnd++;             
        }            
    }        
    //following code block announces the results of the current battle 
    cout << "\n\n******************************************************************************" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "=======================      RESULTS OF BATTLE " << round << "     =========================" << endl;
    cout << "\nPlayer from team 1: " << p1->getName() << " the " << p1->getType() << endl; 
    cout << "Player from team 2: " << p2->getName() << " the " << p2->getType() << endl; 
    cout << "Winner of the battle: " << winner->getName() << endl;
    cout << winner->getName() << " SP points before recovery: " << winner->getSP() << endl;
    winner->recovery(); 
    cout << winner->getName() << " SP points after recovery: " << winner->getSP() << endl;
        
    winner = nullptr; 
    
    return victor;
}
