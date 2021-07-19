/*******************************************************************************    
** Program Name:War Games   
** Author:      Clinton Hawkes
** Date:        04/17/2019
** Description: The Game class is where all the functions and other classes of
                War Games is tied together. The Game class sets up the game, 
                creates the player's Dice, keeps track of the scoring and
                calls all the functions required by the game. More details of
                the function in this class can be found below.
*******************************************************************************/

#include "Game.hpp"
#include "validation.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor
Game::Game(){
    numRounds = 0;
    tieCount = 0;
    p1Score = 0;
    p2Score = 0;
    roundCount = 0; 
    p1Die = nullptr;        //points to player 1 Die object 
    p2Die = nullptr;        //points to player 2 Die object
    p1DieType = "";         //stores player 1 Die type
    p2DieType = "";         //stores player 2 Die type
    winner = "";
}


/*******************************************************************************
** Description: Main menu function is used to greet the player and ask if they
                would like to start the game or quit. If the user wants to quit,
                the game is exited. If the player wants to play, the true bool
                is returned to the calling function and the game begins. 
*******************************************************************************/
bool Game::mainMenu(){
  
    int choice;    //storage for the user's selection

    system("clear");
    
    cout << "Welcome to War Games!" << endl;
    cout << "=======================================================" << endl;
    cout << "1. Start the War Games." << endl;
    cout << "2. Quit" << endl;
    cout << "Please enter the number next to your selection." << endl;

    //gets user input with integerValidation. min=1  max=2 
    choice = integerValidation(1, 2);

    if(choice == 1){        //user want to start simulation 
        cout << endl; 
        return true;
    }
    else{                    //user wants to quit
        cout << "Please come back soon." << endl << endl;
        return false;
    } 
}


/*******************************************************************************
** Description: Run function is where everything comes together. If the user
                selected that they want to play the game, a while loop will 
                begin to loop until the state variable is set to false. Inside
                the while loop is all the logic of the game. First the user is
                asked to setup the number of rounds to be played, the number of
                sides for each die, and the type of die for each player. After 
                the information is gathered, the Die objects are created and 
                the match function is called in a loop for the number of 
                iterations specified. After the match function is done, the 
                final scores are displayed and a winner is announced.
*******************************************************************************/
void Game::run(){
    bool state;         //game will run as long as true
    long temp;

    state = this->mainMenu();   //users choice in menu determins state of game

    while(state == true){

        cout << "How many rounds would you like to play? (min=1/max=100000)" << endl;
        numRounds = integerValidation(1, 100000);
        cout << endl; 

        cout << "What type of Die would you like player 1 to have? (1=regular/2=loaded)" << endl;
        temp = integerValidation(1, 2);
        cout << endl; 
         
        //creates type of die specified for player 1. Type of die is also stored for display purposes 
        if(temp == 1){
            p1Die = new Die;  
            p1DieType = "regular"; 
        }else{
            p1Die = new LoadedDie;
            p1DieType = "loaded"; 
        }
        
        cout << "What type of Die would you like player 2 to have? (1=regular/2=loaded)" << endl;
        temp = integerValidation(1, 2);
        cout << endl; 
         
        //creates type of die specified for player 2. Type of die is also stored for display purposes 
        if(temp == 1){
            p2Die = new Die;  
            p2DieType = "regular";
        }else{
            p2Die = new LoadedDie;
            p2DieType = "loaded"; 
        }
    
        cout << "How many sides would you like the die for player 1 to have? (min=1/max=1000)" << endl;
        temp = integerValidation(1, 1000);
        p1Die->setN(temp);
        cout << endl; 

        cout << "How many sides would you like the die for player 2 to have? (min=1/max=1000)" << endl;
        temp = integerValidation(1, 1000);
        p2Die->setN(temp);
        cout << endl; 
        

        //players are matched against each other for the number of rounds specified by the user. See
        //match function for more indepth explaination of what occurs.
        for(long i = 0; i < numRounds; i++){
            this->match();         
        }
        
        
        //this if/else block calculates the winner of the battle. The winner is then stored in the
        //winner variable to be displayed in the next code block.
        if(p1Score > p2Score){
            winner = "Player 1";
        }
        else if(p2Score > p1Score){
            winner = "Player 2";
        }
        else{
            winner = "BOTH PLAYERS";
        }
        
        //next 5 lines prints out the total rounds won by each player and declares an overall winner. 
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl; 
        cout << "Total number of rounds won by player 1 is " << p1Score << "." << endl;
        cout << "Total number of rounds won by player 2 is " << p2Score << "." << endl;
        cout << "Total number of rounds tied is " << tieCount << "." << endl;
        cout << "##### WINNER IS " << winner << " #####" << endl << endl;

        //the die objects for each player is deleted and the pointers are set to null.
        delete p1Die;
        p1Die = nullptr; 
        delete p2Die;
        p2Die = nullptr; 
        
        //state is set to false so the game ends 
        state = false; 
    }
}


/*******************************************************************************
** Description: Match function is where the war takes place. Each player rolls
                their die by calling the rollDie function and the number each
                player rolls is compared. The player with the highest number
                wins the round.
*******************************************************************************/
void Game::match(){
    
    roundCount++; 
    
    int player1Roll = 0,               //holds player 1 die roll value for current round
        player2Roll = 0;               //holds player 2 die roll value for current round

    player1Roll = p1Die->rollDie();     //player 1 rolls their die
    player2Roll = p2Die->rollDie();     //player 2 rolls their die
    
    cout << "Round number " << roundCount << ":" << endl; 
    
    //the value of each players die, the type of die, and the number of sides on the die is displayed 
    cout << "Player 1 rolled a " << player1Roll << " on their " << p1Die->getN() << " sided " << p1DieType << " die." << endl; 
    cout << "Player 2 rolled a " << player2Roll << " on their " << p2Die->getN() << " sided " << p2DieType << " die." << endl; 
    
    //the following if/else block calculates the winner of the round, prints it to the console, and 
    //increases the winner's total rounds won counter.
    if(player1Roll > player2Roll){
        p1Score++;
        cout << "Player 1 wins the round!" << endl << endl; 
    }
    else if(player1Roll < player2Roll){
        p2Score++;
        cout << "Player 2 wins the round!" << endl << endl; 
    } 
    else{
        tieCount++; 
        cout << "Both players tied this round." << endl << endl;
    }        
        
}
