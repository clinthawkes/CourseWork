/**************************************************************************************************
** Program Name:Linked List
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

#include "LinkedList.hpp"
#include "validation.hpp"
#include <iostream>

//default constructor
LinkedList::LinkedList(){
    
    setHead(nullptr);
    setTail(nullptr);
}

//default destructor deletes all node objects when program terminates
LinkedList::~LinkedList(){

    //loop runs until there are no more nodes remaining in the list 
    while(head != nullptr){
        
        //the last node to be deleted then sets the head and tail to null 
        if(head == tail){

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
            delete head;
            //head points to same node as temp  
            head = temp;
            temp = nullptr;
        }
    }
}

//get function for head address
Node* LinkedList::getHead(){

    return head;
}

//set function for head address
void LinkedList::setHead(Node* H){

    head = H;
}

//get function for tail address
Node* LinkedList::getTail(){

    return tail;
}

//set function for tail address
void LinkedList::setTail(Node* T){

    tail = T;
}

/**************************************************************************************************
** Description: Function is used to print the value of the head node integer variable. If there is
                no head node, an error message informing the user is displayed.
**************************************************************************************************/
void LinkedList::printHead(){

    //prints if there is no head node    
    if(this->getHead()==nullptr){
        
        std::cout << "\n***No head node exists***" << std::endl;
    }
    else{
        
        std::cout << "\nValue of the head node is " << this->getHead()->getVal() << std::endl;
    }
} 

/**************************************************************************************************
** Description: Function is used to print the value of the tail node integer variable. If the is
                no tail node, an error message informing the user is displayed.
**************************************************************************************************/
void LinkedList::printTail(){

    //error message is printed if there is no tail node. 
    if(this->getTail()==nullptr){
        
        std::cout << "\n***No tail node exists***" << std::endl;
    }
    else{
        
        std::cout << "\nValue of the tail node is " << this->getTail()->getVal() << std::endl;
    }
} 
    
/**************************************************************************************************
** Description: Function is used to create a new node at the head of the list. First the user is
                asked what value they would like to store in the node, and then a new node is
                created with the user's provided value, the old head node now points to the new
                head node, and the new head node now points back to the old head node. The new 
                node is now at the head of the list.
**************************************************************************************************/
void LinkedList::newHead(){
    
    int input = 0;          //stores user's input 
    
    std::cout << "\nWhat integer would you like for the new node? (min=-1000/max=1000)" << std::endl;
    std::cout << "Input: ";
    input = integerValidation(-1000,1000);

    Node* temp = head;      //creates a temporary pointer to assist in the making of the new node

    //a new node is created and the head pointer is pointing to it 
    head = new Node(input); 
    
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

    std::cout << "\nNew node with a value of " << input << " has been added to the tail." << std::endl;
    
    //calls the function to traverse the linked list and display all the values in the list 
    this->traverse(); 
}

/**************************************************************************************************
** Description: Function is used to create a new node at the tail of the list. First the user is 
                asked what value they would like to store in the node, and then a new node is
                created with the user's porvided value, the old tail node now points to the new
                tail node, and the new tail node now points back to the old tail node. The new
                node is now at the tail of the list.
**************************************************************************************************/
void LinkedList::newTail(){

    int input = 0;          //stores user's input
    
    std::cout << "\nWhat integer would you like for the new node? (min=-1000/max=1000)" << std::endl;
    std::cout << "Input: ";
    input = integerValidation(-1000,1000);

    //temporary pointer is created to assist in the making of the new tail node 
    Node* temp = tail;

    //new tail node is created and tail is now pointing to it    
    tail = new Node(input);
    
    //if this is the first node in the list, the tail AND the head point to it 
    if(temp == nullptr && head == nullptr){
        
        head = tail;
    }
    //if there is more than one node in the list, the new node and the old node pointe at each other 
    if(temp != nullptr){
        
        temp->setPrev(tail);
        tail->setNext(temp);
    } 
    //temporary pointer is no longer needed 
    temp = nullptr; 
     
    std::cout << "\nNew node with a value of " << input << " has been added to the tail." << std::endl;
    
    //calls the function to traverse the linked list and display all the values in the list 
    this->traverse(); 
}

/**************************************************************************************************
** Description: Function is used to remove the node found at the head of the list. If there is a
                node at the head of the list, the node is deleted and the head now points at the
                node adjacent to the removed node. If there are no nodes in the list, an error
                message is printed to inform the user.
**************************************************************************************************/
void LinkedList::rmHead(){

    //error message prints if there are no nodes in the list to remove 
    if(head == nullptr){ 
        
        std::cout << "\nNothing to remove here" << std::endl; 
    } 
    //if there is only one node in the list, it is removed and the head AND tail are set to null 
    else if(head == tail){

        delete head;                //head node deleted
        head = nullptr;             //head points to null
        tail = nullptr;             //tail points to null
    }
    else{ 
        //temp pointer created and points to the node adjacent to the head node 
        Node* temp = head->getPrev();
        //soon to be head node now points null (no node that direction) 
        temp->setNext(nullptr);
        //node at the head of the list is deleted 
        delete head;
        //head now points to the newly assigned head node 
        head = temp;
        //temp pointer is no longer needed 
        temp = nullptr;
    }
    //calls the function to traverse the linked list and display all the values in the list 
    this->traverse(); 
}

/**************************************************************************************************
** Description: Function is used to remove the node found at the tail of the list. If there is a
                node at the tail of the list, the node is deleted and the tail now points at the
                node adjacent to the removed node. If there are no nodes in the list, an error
                message is printed to inform the user.
**************************************************************************************************/
void LinkedList::rmTail(){

    //error message prints if there are no nodes in the list to remove 
    if(tail == nullptr){ 
        
        std::cout << "\nNothing to remove here" << std::endl; 
    }
    //if there is only one node in the list, it is removed and the tail AND head are set to null 
    else if(tail == head){
        
        delete tail;                //tail node is deleted
        tail = nullptr;             //tail points to null
        head = nullptr;             //head points to null
    }
    else{ 
        //temporary pointer is created and points to the node adjacent to the tail node 
        Node* temp = tail->getNext();
        //soon to be tail node now points to null because there will be no node on that side 
        temp->setPrev(nullptr);
        //node at the tail is deleted 
        delete tail;
        //tail now points at the newly assigned tail node 
        tail = temp;
        //temporary pointer is no longer needed 
        temp = nullptr;
    }
    //calls the function to traverse the linked list and display all the values in the list 
    this->traverse(); 
}

/**************************************************************************************************
** Description: Function is used to display the values of each node in the list starting with the
                head node and ending with the tail node. If there are no nodes in the list, an 
                error message is printed for the user.
**************************************************************************************************/
void LinkedList::traverse(){

    //following only happens if there is a node in the list 
    if(head != nullptr){ 

        //creates a temporary pointer to assist in the printing of all the values 
        Node* start = head;
        
        std::cout << "\nYour linked list is: ";
        
        //loops through all the nodes in the list printing their value 
        while(start){

            std::cout << start->getVal() << " ";
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

/**************************************************************************************************
** Description: Function is used to display the values of each node in the list starting with the
                tail node and ending with the head node. If there are no nodes in the list, an
                error message is printed for the user.
**************************************************************************************************/
void LinkedList::revTraverse(){

    //following only happens if there is a node in the list 
    if(tail != nullptr){
        
        //temporary pointer is created to print all the values without changing the actual tail 
        Node* end = tail;

        std::cout << "\nYour linked list is: ";
        
        //loops through all the nodes in the list while printing each value 
        while(end->getNext() != nullptr){

            std::cout << end->getVal() << " ";
            end = end->getNext();
        }

        //prints the final value in the list 
        std::cout << end->getVal() << std::endl;

        //temporary pointer is no longer needed 
        end = nullptr;
    } 
    //prints if there are no nodes in the list   
    else{
        
        std::cout << "\n*** Your list is empty ***" << std::endl;
    }
}
