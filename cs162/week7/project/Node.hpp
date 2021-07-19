/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/22/2019
** Description: Header file for the Node class. This contains the member variable and function
                declarations for the class. More information about the functions below can be
                found in the Node.cpp file.
**************************************************************************************************/

#ifndef NODE_HPP
#define NODE_HPP
#include "Character.hpp"

class Node{

    private:
        Character* fighter;            //stores node value 
        Node* next;         //pointer storing next node's address
        Node* prev;         //pointer storing previous node's address

    public:
        Node();             //find more details in the Node.cpp file
        Node(Character*);
        Character* getFighter() const;
        void setFighter(Character*);
        Node* getNext() const;
        void setNext(Node*);
        Node* getPrev() const;
        void setPrev(Node*);
};

#endif
