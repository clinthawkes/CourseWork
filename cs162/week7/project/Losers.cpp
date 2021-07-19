/**************************************************************************************************
** Program Name:Fantasy Combat(formerly LinkedList class)
** Author:      Clinton Hawkes
** Date:        05/05/2019
** Description: This is the implementation file for the LinkedList class. This class is used to 
                create and link node objects together to simulate an ordered list of integers. 
                The head node can be thought of as the top of the list and the tail node can be 
                thought of as the end of the list. Each new node that is added stores and integer
                value in its variable and the it is "linked" to the other nodes in the list by
                setting the next/prev pointer variables equal to the nodes adjacent to it. Nodes
                can be added or deleted from the list. The values of all the nodes in the list can
                be printed to the console in accending and decending order. The logic of these
                functions can be found below.
**************************************************************************************************/

#include "Losers.hpp"
#include "validation.hpp"
#include <iostream>
#include "Character.hpp"

//default constructor
Losers::Losers(){
    
    setHead(nullptr);
    setTail(nullptr);
}

//default destructor deletes all node objects when program terminates
Losers::~Losers(){

    //loop runs until there are no more nodes remaining in the list 
    while(head != nullptr){
        
        //the last node to be deleted then sets the head and tail to null 
        if(head == tail){
            delete head->getFighter();
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else{ 
            //temp pointer set to next node up the list 
            Node* temp = head->getPrev();
            //sets the pointer pointing to the head to null 
            temp->setNext(nullptr);
            //deletes head node  
            delete head->getFighter(); 
            delete head;
            //head points to same node as temp  
            head = temp;
            temp = nullptr;
        }
    }
}

//get function for head address
Node* Losers::getHead(){

    return head;
}

//set function for head address
void Losers::setHead(Node* H){

    head = H;
}

//get function for tail address
Node* Losers::getTail(){

    return tail;
}

//set function for tail address
void Losers::setTail(Node* T){

    tail = T;
}

/**************************************************************************************************
** Description: Function is used to create a new node at the head of the list. First the user is
                asked what value they would like to store in the node, and then a new node is
                created with the user's provided value, the old head node now points to the new
                head node, and the new head node now points back to the old head node. The new 
                node is now at the head of the list.
**************************************************************************************************/
void Losers::newHead(Character* fighter){
    
    Node* temp = head;      //creates a temporary pointer to assist in the making of the new node

    //a new node is created and the head pointer is pointing to it 
    head = new Node(fighter); 
    
    //if this is the first node in the list, the head AND the tail will point to it 
    if(temp == nullptr && tail == nullptr){
        
        tail = head;
    }

    //if this was not the first node created in the list, the new node point back to the old node 
    if(temp != nullptr){

        //the old node now points to the new head node 
        temp->setNext(head); 
        //the new head node now points back to the old node 
        head->setPrev(temp);
    }
    //temporary pointer is no longer needed 
    temp = nullptr; 

    //calls the function to traverse the linked list and display all the values in the list 
    //this->traverse(); 
}

/**************************************************************************************************
** Description: Function is used to display the values of each node in the list starting with the
                head node and ending with the tail node. If there are no nodes in the list, an 
                error message is printed for the user.
**************************************************************************************************/
void Losers::traverse(){

    //following only happens if there is a node in the list 
    if(head != nullptr){ 

        //creates a temporary pointer to assist in the printing of all the values 
        Node* start = head;
        
        std::cout << "\nPile of losers: ";
        
        //loops through all the nodes in the list printing their value 
        while(start){

            std::cout << start->getFighter()->getName() << " ";
            start = start->getPrev();
        }
        //temporary pointer is no longer needed 
        start = nullptr; 
    } 
    //prints if there are no nodes in the list   
    else{
        
        std::cout << "\n*** Your list is empty ***" << std::endl;
    }
}
