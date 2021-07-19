/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/14/2019
** Description: Implementation file for the Lineup class. The Lineup class holds the fighters  
                for each team in the tournament. The fighters are held in Node objects.
                Details of the functions used to build the queue structure can be found below. 
**************************************************************************************************/

#include "Lineup.hpp"
#include <iostream>


//default constructor for class
Lineup::Lineup(){

    head = nullptr;
}

//default destructor for class
Lineup::~Lineup(){
    //if there is at least one node in the list, the following will run
    if(head){ 
        //this deletes the front node if there is only one node in the list 
        if(head == head->getNext()){
            delete head->getFighter(); 
            delete head;
            head = nullptr;
        }
        else{
            //this deletes all nodes in a list that has 2 or more nodes 
            Node* temp = head;
            //sets the next variable to null for the last node in the list so the next while
            //statement will know when to stop
            head->getPrev()->setNext(nullptr);
            //deletes all the nodes in the queue 
            while(head){
                temp = head->getNext();
                delete head->getFighter(); 
                delete head;
                head = temp;
            }
        }
    }
}

/**************************************************************************************************
** Description: Function checks to see if the calling Queue object is empty. True is returned
                if it is empty and false is returned if it contains nodes.
**************************************************************************************************/
bool Lineup::isEmpty(){

    //if the list is empty, return true 
    if(!head){
        return true;
    }
    else{
        return false;
    }
}

/**************************************************************************************************
** Description: Function adds a new node to the back of the list with a user specified value
                stored inside. Function preserves the circular link when adding the node. 
**************************************************************************************************/
void Lineup::addBack(Character* person){
    
    //runs if there are no nodes in the list before calling this function 
    if(!head){
        
        head = new Node;       //new node is created and assigned to head
        head->setFighter(person);          //assigns user input to val
        head->setNext(head);          //make list circular by connecting to self
        head->setPrev(head);
    }
    //runs if there is only one node in the list  
    else if(head->getPrev() == head){
        
        Node* back = new Node; //creates a temporary pointer for new node
        
        back->setFighter(person);               //assigns user input to val
        
        back->setPrev(head);               //next 4 lines preserves the circular link for 2 nodes
        back->setNext(head);
        head->setPrev(back);
        head->setNext(back);
        
        back = nullptr;                  //temp pointer no longer needed
    }
    //runs if there are two or more nodes already in the list 
    else{
        
        Node* rear = new Node; //new node assigned to a temporary pointer
        
        rear->setFighter(person);               //user input assigned to new node
        
        rear->setNext(head);               //this block preserves the circular link by reassigning
        rear->setPrev(head->getPrev());         //the next and prev pointers to the appropriate nodes
        head->getPrev()->setNext(rear);
        head->setPrev(rear);
        
        rear = nullptr;                  //no longer need the temp pointer
    } 
}

/**************************************************************************************************
** Description: Function returns the value of the front node when called 
**************************************************************************************************/
Character* Lineup::getFront(){
    
        //val of the front node is returned 
        return head->getFighter();
}

/**************************************************************************************************
** Description: Function will remove the node at the front of the list. The next node in the list
                will be assigned to the head.
**************************************************************************************************/
void Lineup::removeFront(){
    
    //runs if there is only one node in the list     
    if(head->getNext() == head){
        
        delete head;
        head = nullptr;
    }
    //runs if there are two or more nodes in the list 
    else{
        
        Node* temp = head;         //temp pointer to assist in the node removal
        
        head->getNext()->setPrev(head->getPrev());  //next node in queue has prev assigned to last node in queue
        head->getPrev()->setNext(head->getNext());  //last node in queue has next assigned to the new head node
        head = head->getNext();              //head is assigned to the next node of the one being deleted
        
        delete temp;                    //old head or front node is deleted
        temp = nullptr;
    } 
}

/**************************************************************************************************
** Description: Function moves the head to the next Node in the queue.
**************************************************************************************************/
void Lineup::headNext(){

    head = head->getNext();
}



