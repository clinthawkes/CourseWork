/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/14/2019
** Description: Header file for the Lineup class. Lineup has one private
                member variable (pointer to Node), and some member functions for maintenance.
                More information can be found in the implementation file.
**************************************************************************************************/

#ifndef LINEUP_HPP
#define LINEUP_HPP
#include "Node.hpp"
#include "Character.hpp"

//class is used to build the linked list and maintain/modify the list through functions
class Lineup{

    private:
        Node* head;       //points to first object in the list 

    public:
        Lineup();
        ~Lineup();
        bool isEmpty();
        void addBack(Character*);
        Character* getFront();
        void removeFront();
        void headNext(); 
};

#endif
        

        
