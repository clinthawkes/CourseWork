/*************************************************************************************************
** Program Name:OSU Info System 
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Implementation file for the University class. This class is the "brains" of the
                OSU information system. Contains functions needed to make the OSU info system run,
                and is responsible for calling all the functions from other classes as well. The
                OSU Info system stores information about all the buildings and people at OSU. The
                user of the system is able to display this information and even make one of the 
                people at that university do work. More information about the functions can be
                found below with more detail.
**************************************************************************************************/

#include "University.hpp"
#include "menu.hpp"
#include "validation.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor
University::University(){
     
    name = "Oregon State University";
}

//destructor deletes the Building and Person objects on the heap
University::~University(){
    
    //deletes all the Building objects created 
    for(int x = 0; x < buildings.size(); x++){
        delete buildings.at(x);
    }

    //deletes all the Person objects created 
    for(int y = 0; y < people.size(); y++){
        delete people.at(y);
    }
}    

/**************************************************************************************************
** Description: Function prints the name, address and size in square feet of all the buildings
                at OSU entered into the system
**************************************************************************************************/
void University::printBuildingInfo(){

    system("clear"); 
    
    //loops through the vector of Building pointers to print the information specified above 
    for(int i = 0; i < buildings.size(); i++){
        cout << "\nBuilding Name: " << buildings.at(i)->getName() << endl;
        cout << "Building address: " << buildings.at(i)->getAddress() << endl;
        cout << "Size in square feet: " << buildings.at(i)->getSize()<< endl;
    }
    
    //pauses the console so the user can read all the information before continuing 
    cout << "\nPress enter to continue... " << endl; 
    std::cin.get(); 
}


/**************************************************************************************************
** Description: Function prints the name, age and GPA/rating of all the students and instructors
                at OSU. If the person is a Student, it will print their GPA. If the person is an
                Instructor, it will print their rating.
**************************************************************************************************/
void University::printPeopleInfo(){
    
    system("clear"); 

    //loops through the vector of People to print the information specified above 
    for(int j = 0; j < people.size(); j++){
        cout << "\nName: " << people.at(j)->getName() << endl;
        cout << "Age: " << people.at(j)->getAge() << endl;
        people.at(j)->printGrade(); 
    }
    
    //pauses console so user can read the information before continuing 
    cout << "\nPress enter to continue..." << endl; 
    std::cin.get(); 
}


/**************************************************************************************************
** Description: Function 
**************************************************************************************************/
void University::run(){
    
    int choice = 0; 
    bool state = true; 
    
    //creates Building records and enters into system 
    buildings.push_back(new Building("Cordley Hall", "2710 SW Campus Way, Corvallis, OR", 235906));
    buildings.push_back(new Building("Dixon Rec Center", "425 SW 26th Street, Corvallis, OR", 173776));
    buildings.push_back(new Building("Austin Hall", "2751 SW Jefferson Way, Corvallis, OR", 107623));
    
    //creates student records and enters into system 
    people.push_back(new Student("Clint Hawkes", 33, 4.0)); 
    people.push_back(new Student("Ben Lewis", 34, 4.0)); 
    
    //creates instructor records and enters into system 
    people.push_back(new Instructor("Dean Bonney", 53, 2.5)); 
    people.push_back(new Instructor("Jeff Lang", 41, 4.0)); 
    
    //Info system will run until user selects quit 
    while(state == true){ 
        
        system("clear"); 
        
        //displays main menu for user to select option 
        choice = mainMenu();
        
        switch(choice){

            //prints name, address and size of all building at OSU in system 
            case 1: this->printBuildingInfo();
                    break;
            //prints name, age and rating/GPA of every person in system
            case 2: this->printPeopleInfo(); 
                    break;
            //lists all people in system and user selects one to do work
            case 3: this->peopleMenu();
                    break;
            //uer selects quit so program ends
            case 4: state = false;
                    break;
        }
    }
}


/**************************************************************************************************
** Description: Populates a list of all the people at OSU currently entered into the system. The
                user is then asked to select one of the people on the list to "do work". 
**************************************************************************************************/
void University::peopleMenu(){

    int selection = 0;

    system("clear");

    cout << "Please select the number next to the person you would like to do work." << endl << endl;
    
    //prints out a list of all the students and instructors at the university (if entered) 
    for(int r = 0; r < people.size(); r++){
        cout << r+1 << ". " << people.at(r)->getName() << endl << endl;
    } 
    
    //validates that user's entry is within range of people 
    selection = (integerValidation(1, people.size()) - 1);
    
    //calls "do_work" function to print out work statement about chosen person 
    people.at(selection)->do_work();
    
    //pauses console so user can read information before continuing 
    cout << "\nPress enter to continue..." << endl;
    std::cin.get(); 

}
