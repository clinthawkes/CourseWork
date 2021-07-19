/*******************************************************************************    
** Program Name:War Games   
** Author:      Clinton Hawkes
** Date:        04/16/2019
** Description: Header file for the Die class. This contains the class 
                variables and function prototypes. The implementation of these
                can be found in the Die.cpp file. This is the parent class to 
                the LoadedDie class.
*******************************************************************************/

#ifndef DIE_HPP
#define DIE_HPP

class Die{

    protected:
        int N;         //holds number of sides for die

    public:
        Die();
        ~Die();
        void setN(int);
        int getN() const; 
        //virtual function can be overridden by rollDie function in child class 
        virtual int rollDie();     
        
};

#endif
