/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Implementation file for the Zoo class. 
**************************************************************************************************/

#include "Zoo.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>

//default constructor
Zoo::Zoo(){

    message = ""; 
    penguinParents = false;
    tigerParents = false;
    turtleParents = false;
    bankBalance = 23000;
    dayNumber = 0; 
    bonus = 0; 
    numPenguins = 0;
    numTigers = 0;
    numTurtles = 0;
    penguinArraySize = 10; 
    tigerArraySize = 10;
    turtleArraySize = 10;
    penguinList = new Animal*[10];
    tigerList = new Animal*[10];
    turtleList = new Animal*[10];
}

//default destructor deletes all memory used on the heap 
Zoo::~Zoo(){
    
    //deletes all the penguin objects and the dynamic array holding the pointers to them 
    for(int a = 0; a < numPenguins; a++){
        delete penguinList[a];
    }
     
    delete [] penguinList;
    
    //deletes all the tiger objects and the dynamic array holding the pointers to them
    for(int b = 0; b < numTigers; b++){
        delete tigerList[b];
    }
    
    delete [] tigerList;
    
    //deletes all the turtle objects and the dynamic array holding the pointers to them 
    for(int c = 0; c < numTurtles; c++){
        delete turtleList[c];
    }
    
    delete [] turtleList;
}


/**************************************************************************************************
** Description: Function displays the initial menu to the user. They are give a brief description
                of the game and the user can play or quit. If the user wants to play, they are then
                asked how many of each type of animal they would like to purchase. (1 or 2) After
                they purchase animals, the game begins. If the user chooses to quit, the program
                terminates.
**************************************************************************************************/
bool Zoo::mainMenu(){
  
    int choice;    //storage for the user's selection
    int temp;

    system("clear");
    
    cout << "                            Welcome to ZOO Tycoon!                          " << endl;
    cout << "===============================================================================" << endl;
    cout << "                        Current Account Ballance: $" << bankBalance << endl; 
    cout << "===============================================================================" << endl << endl;
    cout << "Zoo tycoon is a game that allows players to run a zoo business. You have the" << endl;
    cout << "chance to own several different types of animals and YOU decide how your  " << endl;
    cout << "business is run. First, you need to purchase some animals for your zoo." << endl << endl;
    cout << "1. Start building my Zoo!" << endl;
    cout << "2. Quit game" << endl << endl;
    cout << "Please enter the number next to your selection." << endl;

    //gets user input with integerValidation. min=1  max=2 
    choice = integerValidation(1, 2);

    if(choice == 2){        //user want to quit simulation 
        cout << "Please come back soon." << endl << endl; 
        return false;
    }
    else{                    //user wants to quit
        
        system("clear");

        cout << "==================================================================================" << endl;
        cout << "Current Account Balance: $" << bankBalance << endl;
        cout << "==================================================================================" << endl;
            
        cout << "\nPenguins will cost you $1,000 each. Would you like to purchase 1 or 2 penguins? " << endl;
        temp = integerValidation(1,2);
     
        //creates 1 or 2 new penguins depending on user's choice     
        if(temp == 1){
            this->addPenguin();
        }
        else{
            this->addPenguin();     //this section creates 2 new penguins
            this->addPenguin();
        }
        
        system("clear");

        cout << "==================================================================================" << endl;
        cout << "Current Account Balance: $" << bankBalance << endl;
        cout << "==================================================================================" << endl;
            
        cout << "\nTigers will cost you $10,000 each. Would you like to purchase 1 or 2 tigers? " << endl;
        temp = integerValidation(1,2);
        
        //creates 1 or 2 new tigers depending on user's choice  
        if(temp == 1){
            this->addTiger();
        }
        else{
            this->addTiger();       //this section creates 2 new tigers
            this->addTiger();
        }
        
        system("clear");

        cout << "==================================================================================" << endl;
        cout << "Current Account Balance: $" << bankBalance << endl;
        cout << "==================================================================================" << endl;
            
        cout << "\nTurtles will cost you $100 each. Would you like to purchase 1 or 2 turtles? " << endl;
        temp = integerValidation(1,2);
        
        //creates 1 or 2 new turtles depending on user's choice 
        if(temp == 1){
            this->addTurtle();
        }
        else{
            this->addTurtle();      //this section creates 2 new turtles
            this->addTurtle();
        }
            
        return true;
    } 
}


/**************************************************************************************************
** Description: This is the function that controls the game. It starts by calling the mainMenu
                so the user can decide whether they want to play or quit. If they want to play,
                then the while loop continues to run until the user decides they want to quit.
                Each loop that runs is a simulation of one "day" at the zoo. First information
                prints out about the current state of the zoo and then functions are called to 
                feed animals, produce random events, collect revenue, buy animals and recap at the
                end of the day. More details of this function can be found below.
**************************************************************************************************/
void Zoo::run(){

    bool state = true;
    char buy;
    int input = 0; 

    //user chooses to play or quit at mainMenu. The answer controls the while loop. True = play 
    state = this->mainMenu();
    
    while(state == true){

        system("clear");
        
        //increases age of all animals in zoo by 1 
        this->ageAnimals(); 
        //sets bool to true for each type of animal if there is one that is age 3 
        this->checkIfAdult(); 
        
        dayNumber++;  
        
        cout << "Start of day number " << dayNumber << "." << endl << endl;
        
        cout << "==================================================================================" << endl;
        cout << "Today's Beginning Account Balance: $" << bankBalance << endl;
        cout << "==================================================================================" << endl;
        
        cout << "\nZoo Inventory at the start of the day:" << endl << endl;
        cout << "Number of penguins: " << numPenguins << endl;
        cout << "  Number of tigers: " << numTigers << endl;
        cout << " Number of turtles: " << numTurtles << endl;

        //calculates the cost to feed the current zoo inventory and informs user 
        cout << "\nTotal cost to feed your animals today is $" << this->dailyCost() << endl << endl;
        //deducts food cost from bank 
        bankBalance -= this->dailyCost(); 
        
        //calls the random event function each day 
        cout << "##### Today's Random Event #####" << endl;
        this->randomEvent();

        //calculates the revenue produced by the current zoo inventory and informs user
        cout << "Your revenue for today, not including bonuses, is $" << this->dailyPayoff() << "." << endl << endl;
        //adds revenue to bank 
        bankBalance += this->dailyPayoff(); 
        
        //user has option to purchase and animal each day 
        cout << "Would you like to purchase an adult animal today? (yes/no):  ";
        buy = yesNoValidation();
        
        //if user chooses yes, the buyAdult function is called 
        if(buy == 'y'){
            this->buyAdult();
        }

        cout << "\n==================================================================================" << endl;
        cout << "Today's Ending Account Balance: $" << bankBalance << endl;
        cout << "==================================================================================" << endl;
        
        cout << "\nEnter 1 to start the next day. Enter 0 to quit." << endl; 
        
        input = integerValidation(0, 1);
        
        //if user chooses to quit, the loop stops and program is terminated 
        if(input == 0){
            state = false;
        }
        
        //resets certain variables back to zero for the start of the next day 
        this->endOfDay();
        
        //if the user has no money, the game will end 
        if(bankBalance <=0){
            cout << "You ran out of money and filed for bankruptcy. Good luck next time." << endl << endl;
            state = false;
        }
        //if the user has 50 million or more in the bank, the game ends 
        if(bankBalance > 50000000){
            cout << "You built a successful business and decide to retire! Congrats on your success!!!!" << endl << endl;
            state = false;
        }
    }
}


/**************************************************************************************************
** Description: Function adds a Penguin to the zoo. First the function checks to see how many 
                Penguins are in the zoo. If the number of Penguins is the same as the max size
                of the array holding the Penguins, then the size of the array is doubled and the
                addresses of the old array is copied to the new array. Then the old array is 
                deleted and a new Penguin is added to the new (bigger) array. If the array holding
                the Penguins was not at capacity, then a new Penguin is added without modifying the
                array.
**************************************************************************************************/
void Zoo::addPenguin(){ 
    
    //checks to see if there is room in the array to add a Penguin. If not, the following code executes 
    if(numPenguins == penguinArraySize){
        
        //variable tracking the size of the Penguin array is doubled 
        penguinArraySize *= 2; 
        
        //temporary array of Penguins is created with the new size 
        Animal** temp = new Animal*[penguinArraySize];
        
        //the pointers are copied from the old outgrown array to the new array 
        for(int i = 0; i < numPenguins; i++){
            temp[i] = penguinList[i];
        }
        
        //the old array is deleted and the temporary array is assigned to Penguin list 
        delete [] penguinList; 
        penguinList = temp;
        temp = nullptr;
        
        //a new Penguin is created and added to the next open spot in the array 
        penguinList[numPenguins] = new Penguin;
        //the cost of the penguin is taken out of the bank 
        bankBalance -= penguinList[numPenguins]->getCost(); 
        numPenguins++;
        }
        
    //if the array is not at capacity, the following code executes 
    else if(numPenguins < penguinArraySize){

        //a new Penguin is created and added to the next open spot in the array  
        penguinList[numPenguins] = new Penguin;
        //the cost of the Penguin is taken out of the bank 
        bankBalance -= penguinList[numPenguins]->getCost(); 
        numPenguins++;
    }
}

/**************************************************************************************************
** Description: Function adds a Tiger to the zoo. First the function checks to see how many 
                Tigers are in the zoo. If the number of Tigers is the same as the max size
                of the array holding the Tigers, then the size of the array is doubled and the
                addresses of the old array is copied to the new array. Then the old array is 
                deleted and a new Tiger is added to the new (bigger) array. If the array holding
                the Tigers was not at capacity, then a new Tiger is added without modifying the
                array.
**************************************************************************************************/
void Zoo::addTiger(){

    //checks to see if there is room in the array to add a Tiger. If not, the following code executes 
    if(numTigers == tigerArraySize){
        
        //variable tracking size of the Tiger array is doubled 
        tigerArraySize *= 2; 
        
        //temporary array of Tigers is created with the new double size 
        Animal** temp = new Animal*[tigerArraySize];
        
        //pointers are copied from the old outgrown array to the new array 
        for(int i = 0; i < numTigers; i++){
            temp[i] = tigerList[i];
        }
        
        //the old array is deleted and the new array is assigned to the Tiger list 
        delete [] tigerList; 
        tigerList = temp;
        temp = nullptr;
        
        //a new tiger is created and added to the next open spot in the array  
        tigerList[numTigers] = new Tiger;
        //the cost of the Tiger is taken out of the bank 
        bankBalance -= tigerList[numTigers]->getCost(); 
        numTigers++;
        }
        
    //if the Tiger array is not at capacity, the following code executes 
    else if(numTigers < tigerArraySize){

        //a new Tiger is added to the next open spot in the Tiger array 
        tigerList[numTigers] = new Tiger;
        //cost of the Tiger is taken out of the bank 
        bankBalance -= tigerList[numTigers]->getCost(); 
        numTigers++;
    }
}


/**************************************************************************************************
** Description: Function adds a Turtle to the zoo. First the function checks to see how many 
                Turtles are in the zoo. If the number of Turtles is the same as the max size
                of the array holding the Turtles, then the size of the array is doubled and the
                addresses of the old array is copied to the new array. Then the old array is 
                deleted and a new Turtle is added to the new (bigger) array. If the array holding
                the Turtles was not at capacity, then a new turtle is added without modifying the
                array.
**************************************************************************************************/
void Zoo::addTurtle(){

    //checks to see if there is room in the array to add a turtle. If not, the following code executes 
    if(numTurtles == turtleArraySize){
        
        //variable tracking size of the Turtle array is doubled 
        turtleArraySize *= 2; 
        
        //temporary array of Turtles is created with the new doubled size 
        Animal** temp = new Animal*[turtleArraySize];
        
        //pointers are copied from the outgrown array to the new array 
        for(int i = 0; i < numTurtles; i++){
            temp[i] = turtleList[i];
        }
        
        //the old array is deleted and the temporary array is assigned to Turtle list 
        delete [] turtleList; 
        turtleList = temp;
        temp = nullptr;
        
        //a new Turtle is added to the next open spot in the array 
        turtleList[numTurtles] = new Turtle;
        //the cost of the Turtle is taken out of the bank 
        bankBalance -= turtleList[numTurtles]->getCost(); 
        numTurtles++;           //Turtle counter is increased 
        }
        
    //if the Turtle array is not at capacity, the following code executes 
    else if(numTurtles < turtleArraySize){
        
        //a new Turtle is added to the next open spot in the Turtle array 
        turtleList[numTurtles] = new Turtle;
        //cost of the new Turtle is taken out of the bank 
        bankBalance -= turtleList[numTurtles]->getCost(); 
        numTurtles++;           //Turtle counter is increased
    }
}


/**************************************************************************************************
** Description: Function is used to remove a Penguin from the zoo. First the function checks to
                make sure there is a Penguin to remove, then id deletes the last Penguin added to
                the zoo. After the Penguin is removed, the variable keeping track of the total
                number of Penguins in the zoo is decreased by 1.
**************************************************************************************************/
void Zoo::removePenguin(){

    //checks to see if there is a Penguin to remove. 
    if(numPenguins > 0){
        //deletes the last Penguin added to the zoo 
        delete penguinList[(numPenguins-1)];
        penguinList[(numPenguins-1)] = nullptr;
        numPenguins--;      //decreases the Penguin counter by 1
    }
}

/**************************************************************************************************
** Description: Function is used to remove a Tiger from the zoo. First the function checks to
                make sure there is a Tiger to remove, then it deletes the last Tiger added to
                the zoo. After the Tiger is removed, the variable keeping track of the total
                number of Tigers at the zoo is decreased by 1.
**************************************************************************************************/
void Zoo::removeTiger(){
    
    //checks to see if there is a Tiger to remove. 
    if(numTigers > 0){
        //deletes the last Tiger added to the zoo 
        delete tigerList[(numTigers - 1)];
        tigerList[(numTigers - 1)] = nullptr; 
        numTigers--;        //decreases the Tiger counter by 1
    }
}

/**************************************************************************************************
** Description: Function is used to remove a Turtle from the zoo. First the function checks to 
                make sure there is a Turtle to remove, then it deletes the last Turtle added to
                the zoo. After the Turtle is removed, the variable keeping track of the total
                number of Turtles is decreased by 1.
**************************************************************************************************/
void Zoo::removeTurtle(){
    
    //checks to see if there is a turtle to remove. 
    if(numTurtles > 0){
        //deletes the last turtle added to the zoo 
        delete turtleList[(numTurtles - 1)];
        turtleList[(numTurtles - 1)] = nullptr;
        numTurtles--;       //decreases the Turtle counter by 1
    }
}

/**************************************************************************************************
** Description: Function is used to randomly choose an event to happen each day.
**************************************************************************************************/
void Zoo::randomEvent(){

    int event;

    event = rand()%4;           //random number between 0 and 3 is generated to determine event
    
    switch(event){

        //if 0 is generated, an animal is going to get sick and the function is called 
        case 0: this->sickness();
                break;

        //if 1 is generated, a boom in attendance is going to happen and the function is called 
        case 1: this->boom();
                break;

        //if 2 is generated, an animal at the zoo is going to give birth and the function is called 
        case 2: this->babyBorn();
                break;
        
        //no event happens if 3 is generated. The following message is shown        
        //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
        case 3: outFile.open("text.txt"); 
                outFile << "No random event for today... " << endl;
                outFile.close(); 
                inFile.open("text.txt");
                while(!inFile.fail() && !inFile.eof()){
                    getline(inFile, message);
                    cout << message << endl;
                }            
                inFile.close(); 
                break;
    }
}

/**************************************************************************************************
** Description: Function is called when the randomEvent() function randomly decides that an 
                animal in the zoo should get sick and die. First the function checks to see if
                there are any animals. If there are no animals, a statement is printed saying that.
                If there are some animals, a random number is generated to decide which type of 
                animal should get sick and die. If an animal is chosen to die and there are one
                or more of that type of animal, one is removed from the zoo.
**************************************************************************************************/
void Zoo::sickness(){
    
    int animal;                     //holds random number deciding which animal gets sick
    bool status = true;             //controls the while loop below

    //checks to make sure there are any animals in the zoo before continuing
    if(numPenguins == 0 && numTigers == 0 && numTurtles == 0){
        
        //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
        outFile.open("text.txt"); 
        outFile << "Your zoo does not have any animals." << endl;
        outFile.close(); 
        inFile.open("text.txt");
        while(!inFile.fail() && !inFile.eof()){
            getline(inFile, message);
            cout << message << endl;
        }            
        inFile.close(); 
        
        status = false;             //terminates function if no animals
    }
    
    while(status == true){ 
        
        animal = rand()%3;          //random number between 0 and 2 is generated to decide which animal gets sick

        //if rand number is 0 and there are penguins, one is removed and a statement is printed informing user 
        if(animal == 0 && numPenguins > 0){
            this->removePenguin();
            
            //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
            outFile.open("text.txt"); 
            outFile << "One of your penguins got sick and died. You now have " << numPenguins << " penguins." << endl; 
            outFile.close(); 
            inFile.open("text.txt");
            while(!inFile.fail() && !inFile.eof()){
                getline(inFile, message);
                cout << message << endl;
            }            
            inFile.close(); 
            
            status = false;         //used to escape loop 
        }
        //if rand number is 1 and there are tigers, then one is removed and a statement is printed informing user 
        else if(animal == 1 && numTigers > 0){
            this->removeTiger();
            
            //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
            outFile.open("text.txt"); 
            outFile << "One of your tigers got sick and died. You now have " << numTigers << " tigers." << endl; 
            outFile.close(); 
            inFile.open("text.txt");
            while(!inFile.fail() && !inFile.eof()){
                getline(inFile, message);
                cout << message << endl;
            }            
            inFile.close(); 
            
            status = false;         //used to escape loop    
        }
        //if rand number is 2 and there are turtles, then on is removed and a statement is printed informing user 
        else if(animal == 2 && numTurtles > 0){
            this->removeTurtle();
            
            //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
            outFile.open("text.txt"); 
            outFile << "One of your turtles got sick and died. You now have " << numTurtles << " turtles." << endl; 
            outFile.close(); 
            inFile.open("text.txt");
            while(!inFile.fail() && !inFile.eof()){
                getline(inFile, message);
                cout << message << endl;
            }            
            inFile.close(); 
            
            status = false;         //used to escape loop
        }
    }
}    

/**************************************************************************************************
** Description: Function is called when the randomEvent() function randomly decides that there
                was a boom in zoo attendance. First the function checks if there are any tigers
                at the zoo. If there isn't, a statment is printed saying there are no tigers for
                the bonus. If there are tigers, a random number between 250 and 500 is generated,
                that number is multiplied by the number of tigers at the zoo, and a statement
                is printed saying the total bonus earned for the day. That ammount is added to the
                bankAccount.
**************************************************************************************************/
void Zoo::boom(){
    
    int temp; 
    
    //check to see if there are any tigers at the zoo. If none, the following message is shown
    if(numTigers == 0){
        
        //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
        outFile.open("text.txt"); 
        outFile << "You don't have any tigers for the bonus." << endl;
        outFile.close(); 
        inFile.open("text.txt");
        while(!inFile.fail() && !inFile.eof()){
            getline(inFile, message);
            cout << message << endl;
        }            
        inFile.close(); 
    }
    else{
        temp = rand()%251 + 250;    //generates number between 250 and 500
        bonus = temp * numTigers;   //calculates total bonus
        bankBalance += bonus;       //adds bonus to bank
        
        //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
        outFile.open("text.txt"); 
        outFile << "There was a BOOM in zoo attendance today!" << endl; 
        outFile << "You received a $" << temp << " bonus for each of your " << numTigers << " tigers." << endl;
        outFile << "Your total bonus received is $" << bonus << "." << endl;
        outFile.close(); 
        inFile.open("text.txt");
        while(!inFile.fail() && !inFile.eof()){
            getline(inFile, message);
            cout << message << endl;
        }
        inFile.close(); 
    }    
}

/**************************************************************************************************
** Description: Function is called when the randomEvent() function randomly decides that an
                animal in the zoo should have babies. First the function checks to see if any 
                animals are old enough to have babies. If some are , then a loop is started and it
                runs until one of the animals that are old enough to have babies is randomly 
                chosen. The babies that are born are set to have an age of 0.
**************************************************************************************************/
void Zoo::babyBorn(){
    
    bool status = true;         //controls the while loop below
    
    //checks to see if at least one type of animal can have babies. If none are old enough to have 
    //babies, no babies are born and a message stating that is printed
    if(penguinParents == false && tigerParents == false && turtleParents == false){
        
        //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
        outFile.open("text.txt"); 
        outFile << "There are no adult animals, so no babies are born today." << endl;
        outFile.close(); 
        inFile.open("text.txt");
        while(!inFile.fail() && !inFile.eof()){
            getline(inFile, message);
            cout << message << endl;
        }            
        inFile.close(); 
        
        status = false;             //prevents entering loop
    }
    
    while(status == true){ 
        
        int animal = rand()%3;      //random number between 0 and 2 decides which animal gives birth

        //if random number is 0 and there is a penguin old enough to give birth, 5 babies are born
        if(animal == 0 && penguinParents == true){
            for(int i = 0; i < 5; i++){
                this->addPenguin();
                //since the addPenguin() automatically deducts the price of a penguin, this adds it back 
                bankBalance += penguinList[(numPenguins-1)]->getCost();
                penguinList[(numPenguins-1)]->setAge(0);    //sets age of penguin to 0
            }
            
            //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
            outFile.open("text.txt"); 
            outFile << "One of your penguins had 5 eggs hatch!" << endl; 
            outFile.close(); 
            inFile.open("text.txt");
            while(!inFile.fail() && !inFile.eof()){
                getline(inFile, message);
                cout << message << endl;
            }            
            inFile.close(); 
            
            //used to escape the while loop 
            status = false;         
        } 
        
        //if random number is 1 and there is a tiger old enough to give birth, one tiger cub is born 
        else if(animal == 1 && tigerParents == true){
            this->addTiger();
            //since the addTiger() function automatically deducts the price of a tiger, this adds it back 
            bankBalance += tigerList[(numTigers-1)]->getCost();
            tigerList[(numTigers-1)]->setAge(0);            //sets age of tiger to 0
            
            //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
            outFile.open("text.txt"); 
            outFile << "One of your tigers gave birth to a cub!" << endl; 
            outFile.close(); 
            inFile.open("text.txt");
            while(!inFile.fail() && !inFile.eof()){
                getline(inFile, message);
                cout << message << endl;
            }            
            inFile.close(); 
            
            //used to escape the while loop 
            status = false; 
            
        } 
        //if the random number is 2 and there is a turtle old enough to give birth, 10 turtles are born 
        else if(animal == 2 && turtleParents == true){
            for(int k = 0; k < 10; k++){
                this->addTurtle();
                //since the addTurtle() automatically deducts the price of a turtle, this adds it back 
                bankBalance += turtleList[(numTurtles-1)]->getCost();
                turtleList[(numTurtles-1)]->setAge(0);      //sets age of turtle to 0
            }
            
            //next 9 lines opens text file, saves message, close file, opens file, reads message, closes file 
            outFile.open("text.txt"); 
            outFile << "One of your turtles had 10 eggs hatch!" << endl; 
            outFile.close(); 
            inFile.open("text.txt");
            while(!inFile.fail() && !inFile.eof()){
                getline(inFile, message);
                cout << message << endl;
            }            
            inFile.close(); 
            
            //used to escape the while loop 
            status = false; 
        } 
    }        
}

/**************************************************************************************************
** Description: Function calculates the daily cost to feed the animals in the zoo. The number
                of each type of animal is multiplied by their respective cost of food. The values
                are then summed and returned to the calling object.
**************************************************************************************************/
int Zoo::dailyCost(){
     
    return (numPenguins * 10) + (numTigers * 50) + (numTurtles * 5);
}

/**************************************************************************************************
** Description: Function calculates the daily payoff by multiplying the current number of each 
                animal by their respective payout amount. That calculation is then returned to the
                calling object.
**************************************************************************************************/
int Zoo::dailyPayoff(){
     
    return (numPenguins * 100) + (numTigers * 2000) + (numTurtles * 5);
}


/**************************************************************************************************
** Description: Function increases the age of all animals by 1 day. This is called at the beginning
                of each day.
**************************************************************************************************/
void Zoo::ageAnimals(){

    //cycles through all penguins and increases age by one 
    for(int i = 0; i < numPenguins; i++){
        penguinList[i]->increaseAge();
    }

    //cycles through all tigers and increases age by one 
    for(int j = 0; j < numTigers; j++){
        tigerList[j]->increaseAge();
    }

    //cycles through all turtles and increase age by one 
    for(int k = 0; k < numTurtles; k++){
        turtleList[k]->increaseAge();
    }
}


/**************************************************************************************************
** Description: Function is called at the start of each day to check if the various animals are
                old enough to have babies. This information is required by the random event 
                function that randomly chooses a type of animal to have babies. Animals die during
                the day and new animals are bought at the end of the day so this must be checked at
                the start of the day.
**************************************************************************************************/
void Zoo::checkIfAdult(){

    //checks the age of all Penguins and sets the pengiunParents variable to true if at least one is age 3 
    for(int i = 0; i < numPenguins; i++){
        int days = penguinList[i]->getAge();    //stores age of penguin in days variable
        if(days >= 3){                          //checks if age is 3 or greater
            penguinParents = true;              //sets penguinParents to true if days >= 3
        }                                       //process repeates for the other animals below
    }

    //checks the age of all Tigers and sets the tigerParents variable to true if at least one is age 3 
    for(int j = 0; j < numTigers; j++){
        int days = tigerList[j]->getAge();
        if(days >= 3){
            tigerParents = true;
        }
    }

    //checks the age of all Turtles and sets the turtlePartents variable to true if at least one is age 3 
    for(int k = 0; k < numTurtles; k++){
        int days = turtleList[k]->getAge();
        if(days >= 3){
            turtleParents = true;
        }
    }
}


/**************************************************************************************************
** Description: Function is used at the end of each day to reset the variables that need to be
                populated at the start of each day. The three "Parents" variables determine
                if each type of animal is able to have babies and the bonus variable stores
                the bonus earned for each day. If no bonus is earned it needs to be 0.
**************************************************************************************************/
void Zoo::endOfDay(){
    
    penguinParents = false;
    tigerParents = false;
    turtleParents = false;
    bonus = 0;
}


/**************************************************************************************************
** Description: Function is called when the user wants to buy an adult animal at the end of the
                day. The user is given the name and price of the animals to choose from. If the
                user does not have enough money in the bank, a message will tell them and ask
                for another entry. If the user has enough money, the animal is purchased, the age
                of that animal is set to 3 and a message prints on the screen detailing the 
                transaction.
**************************************************************************************************/
void Zoo::buyAdult(){

    int temp;                   //temporarily stores user selection
    bool status = true;         //controls the while loop below 

    cout << "\nPlease enter the number next to the animal you would like to purchase." << endl << endl;

    cout << "1) Penguin for $1,000";
    cout << "                   Updated Balance: $" << bankBalance << endl; 
    cout << "2) Tiger for $10,000" << endl;
    cout << "3) Turtle for $100" << endl;
    cout << "4) Don't make a purchase." << endl << endl; 

    //loop continues until the user as made a selection that does not exceed their funds 
    while(status == true){

        cout << "Option number: ";
        temp = integerValidation(1, 4);

        //purchases a Penguin if the user has 1000 dollars in the bank 
        if(temp == 1 && bankBalance > 1000){
            
            status = false; 
        }
        //purchases a Tiger if the user has 10000 dollars in the bank 
        else if(temp == 2 && bankBalance > 10000){
            
            status = false; 
        }
        //purchases a Turtle if the user has 100 dollars in the bank 
        else if(temp == 3 && bankBalance > 100){
            
            status = false; 
        }        
        //sets the status flag to false to escape loop when user decides not to purchase an animal 
        else if(temp == 4){
            
            status = false;
        }
        else{
            cout << "You don't have enough money. Please make another selection." << endl;
        }
    }        
        
    //switch statemenent uses the option selected by the user above 
    switch(temp){

        //user chose to purchase penguin, so a penguin is added using addPenguin() and the age is set to 3 
        case 1: this->addPenguin();
                penguinList[numPenguins-1]->setAge(3);
                cout << "\nYou bought a penguin for $" << penguinList[numPenguins-1]->getCost() << endl; 
                break;

        //user chose to purchase a tiger, so a Tiger is added using addTiger() and the age is set to 3        
        case 2: this-> addTiger();
                tigerList[numTigers-1]->setAge(3);
                cout << "\nYou bought a tiger for $" << tigerList[numTigers-1]->getCost() << endl; 
                break;
                
        //user chose to purchase a turtle, so a Turtle is added using addTurtle() and the age is set to 3
        case 3: this->addTurtle();
                turtleList[numTurtles-1]->setAge(3);
                cout << "\nYou bought a turtle for $" << turtleList[numTurtles-1]->getCost() << endl; 
                break;

        //user chose not to purchase an animal at this time, so nothing happens 
        case 4: break;
    }

}
