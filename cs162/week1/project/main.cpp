/*******************************************************************************    
** Program Name:Langton's Ant
** Name:        Clinton Hawkes
** Date:        04/08/2019
** Description: Langton's Ant simulation begins by asking a user to provide some
                information to setup the game board to their liking. This 
                includes size of board, number of iterations, and the starting 
                location of the Ant. After the required information has been 
                entered, the simulation begins, and the Ant sets off on an 
                autonomous journey. During the simulation, the Ant automatically
                reacts to various conditions on the game board giving the "Ant"
                the appearance of moving and turning accordingly. If the 
                simulation is run for >12000 iterations, a pattern will emerge.
*******************************************************************************/

#include <cstdlib>              
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "menu.hpp"
#include "ant.hpp"
#include "validation.hpp"

int main(){

    bool state;                 //variable used to control state of simulation 
    
    system("clear");

    state = mainMenu();         //state of simulation determined by users choice in menu

    if(state == false){         //if user chose quit in the menu, program ends
        return 0;
    }
    
    Ant user;                   //Ant object is created
    char answer; 
    int temp,
        count = 0;              //loop counter is initialized to zero

    //loop containing logic of simulation. Simulation will continue to loop unless
    //user selects quit from the menu
    while(state == true){ 
    
        system("clear"); 
        cout << "####EXTRA CREDIT TASK IS COMPLETE. OPTION FOR ANT RANDOM START AVAILABLE####" << endl;
        
        //next four code blocks asks user for input, validates it, and then sets the variable.
        //the validation function is given the min and max values allowed for the situation
        cout << "Would you like the ant to start at a random location? (y=yes/n=no)" << endl;
        answer = yesNoValidation();     //if anser is yes, the ant will start at random location
        
        cout << "How many rows would you like the board to have? (min=5/max=200)" << endl;
        temp = integerValidation(5, 200); 
        user.setNumRow(temp);

        cout << "How many columns would you like the board to have? (min=5/max=200)" << endl;
        temp = integerValidation(5, 200);
        user.setNumCol(temp);

        cout << "How many steps would you like the simulation to perform? (min=10/max=20000)" << endl;
        temp = integerValidation(1, 20000);
        user.setNumSteps(temp);
    
        if(answer == 'y'){
            int row,                //temporary holders for Ant's random start location
                col;

            srand(time(NULL));      //seeding the random generator

            row = rand() % user.getNumRow();    //random row location is generated
            user.setAntX(row);

            col = rand() % user.getNumCol();    //random col location is generated
            user.setAntY(col);
        }
        
        //if random start location for Ant is not wanted, the following lines are executed. 
        //the user is asked what row and column they would like the Ant to begin on.
        else if(answer == 'n'){
            cout << "What row would you like the ant to start on? (min=0/max=" << (user.getNumRow()-1) << ")" << endl;
            temp = integerValidation(0, (user.getNumRow() - 1));    //user input is validated
            user.setAntX(temp);

            cout << "What column would you like the ant to start on?" << endl;
            temp = integerValidation(0, (user.getNumCol() - 1));    //user input is validated
            user.setAntY(temp);
        }
        
        user.createBoard();             //the game board is created according to user spec

        //loop will run until the number of steps specified by user are completed 
        while(count <= user.getNumSteps()){

            cout << endl << endl;
            user.printBoard();          //prints game board
            user.changeOrient();        //changes Ant's orientation
            user.changeColor();         //changes color of board at Ant's location
            user.advance();             //the Ant advances one space
            count++;
        }
     
        state = secondaryMenu();        //uses menu to ask user continue or quit 
        
        count = 0;                      //resets counter
        
        if(state == true){              //if user continues, the game board is reset
            user.~Ant(); 
        } 
    }
    
    return 0;
    
}
    
