/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Header file for the Animal class. This file contains the member variables and 
                function prototypes for the class. More details about the functions can be found
                in the Animal.cpp file. 
**************************************************************************************************/

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Animal {

    protected:
        const int BASE_FOOD_COST = 10;          //constant food cost
        int age,
            cost,
            numberOfBabies,
            payoff;

    public:
        Animal();
        int getAge();
        void setAge(int);
        int getCost();
        int getNumberOfBabies();
        //virtual function to be overridden by derived classes 
        virtual int getDailyFoodCost(); 
        //virtual function to be overridden by derived classes 
        virtual int getPayOff();
        void increaseAge();
};

#endif
