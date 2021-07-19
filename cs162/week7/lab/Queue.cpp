/**************************************************************************************************
** Program Name:Circular List
** Author:      Clinton Hawkes
** Date:        05/14/2019
** Description: Implementation file for the QueueNode struct and the Queue class. The QueueNode
                struct are like the links in a chain, and the Queue class puts the links together.
                Details of the functions used to build the queue structure can be found below. 
**************************************************************************************************/

#include "Queue.hpp"
#include <iostream>


//default constructor for struct
QueueNode::QueueNode(){

    next = nullptr;
    prev = nullptr;
    val = 0;
}

//default constructor for class
Queue::Queue(){

    head = nullptr;
}

//default destructor for class
Queue::~Queue(){
    //if there is at least one node in the list, the following will run
    if(head){ 
        //this deletes the front node if there is only one node in the list 
        if(head == head->next){
            delete head;
            head = nullptr;
        }
        else{
            //this deletes all nodes in a list that has 2 or more nodes 
            QueueNode* temp = head;
            //sets the next variable to null for the last node in the list so the next while
            //statement will know when to stop
            head->prev->next = nullptr;
            //deletes all the nodes in the queue 
            while(head){
                temp = head->next;
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
bool Queue::isEmpty(){

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
void Queue::addBack(int value){
    
    //runs if there are no nodes in the list before calling this function 
    if(!head){
        
        head = new QueueNode;       //new node is created and assigned to head
        head->val = value;          //assigns user input to val
        head->next = head;          //make list circular by connecting to self
        head->prev = head;
    }
    //runs if there is only one node in the list  
    else if(head->prev == head){
        
        QueueNode* back = new QueueNode; //creates a temporary pointer for new node
        
        back->val = value;               //assigns user input to val
        
        back->prev = head;               //next 4 lines preserves the circular link for 2 nodes
        back->next = head;
        head->prev = back;
        head->next = back;
        
        back = nullptr;                  //temp pointer no longer needed
    }
    //runs if there are two or more nodes already in the list 
    else{
        
        QueueNode* rear = new QueueNode; //new node assigned to a temporary pointer
        
        rear->val = value;               //user input assigned to new node
        
        rear->next = head;               //this block preserves the circular link by reassigning
        rear->prev = head->prev;         //the next and prev pointers to the appropriate nodes
        head->prev->next = rear;
        head->prev = rear;
        
        rear = nullptr;                  //no longer need the temp pointer
    } 
}

/**************************************************************************************************
** Description: Function returns the value of the front node when called 
**************************************************************************************************/
int Queue::getFront(){
    
        //val of the front node is returned 
        return head->val;
}

/**************************************************************************************************
** Description: Function will remove the node at the front of the list. The next node in the list
                will be assigned to the head.
**************************************************************************************************/
void Queue::removeFront(){
    
    //runs if there is only one node in the list     
    if(head->next == head){
        
        delete head;
        head = nullptr;
    }
    //runs if there are two or more nodes in the list 
    else{
        
        QueueNode* temp = head;         //temp pointer to assist in the node removal
        
        head->next->prev = head->prev;  //next node in queue has prev assigned to last node in queue
        head->prev->next = head->next;  //last node in queue has next assigned to the new head node
        head = head->next;              //head is assigned to the next node of the one being deleted
        
        delete temp;                    //old head or front node is deleted
        temp = nullptr;
    } 
}


/**************************************************************************************************
** Description: Function prints the list of node values from head to end.
**************************************************************************************************/
void Queue::printQueue(){

    QueueNode* temp = head;             //temporary pointer used for printing values
    
    std::cout << "\nYour queue is: "; 
    
    //all the node values will print, one by one, until it returns to the head.  
    do{
        std::cout << temp->val << " ";
        temp = temp->next;
    } while(temp != head);
    
    std::cout << std::endl;             //used for formatting
}
