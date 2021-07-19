/**************************************************************************************************
** Program Name:Linked List 
** Author:      Clinton Hawkes
** Date:        05/05/2019
** Description: Header file for the LinkedList class. File contains the member variables and the
                function declarations for the class. Further information regarding the details of
                the declarations found below can be viewed in the LinkedList.cpp file. There you
                will find indepth explanations of each function.
**************************************************************************************************/

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include "Node.hpp"

class LinkedList{

    private:
        Node* head;         //pointer storing head node address
        Node* tail;         //pointer storing tail node address

    public:                 //find details in LinkedList.cpp
        LinkedList();
        ~LinkedList();  
        Node* getHead();
        void setHead(Node*);
        Node* getTail();
        void setTail(Node*);
        void printHead();
        void printTail();
        void newHead();
        void newTail();
        void rmHead();
        void rmTail();
        void traverse();
        void revTraverse();

};

#endif
        
