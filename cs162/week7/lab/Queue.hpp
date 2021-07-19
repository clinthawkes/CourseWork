/**************************************************************************************************
** Program Name:Circular List
** Author:      Clinton Hawkes
** Date:        05/14/2019
** Description: Header file for the Queue class and the QueueNode struct. Queue has one private
                member variable (pointer to QueueNode) and QueueNode has three public member
                variables. More information can be found in the implementation file.
**************************************************************************************************/

#ifndef QUEUE_HPP
#define QUEUE_HPP

//structure used to build circular linked lists
struct QueueNode{

    QueueNode* next;        //stores address of next node
    QueueNode* prev;        //stores address of previous node
    int val;                //stores value assigned by user
    QueueNode();             
};

//class is used to build the linked list and maintain/modify the list through functions
class Queue{

    private:
        QueueNode* head;       //points to first object in the list 

    public:
        Queue();
        ~Queue();
        bool isEmpty();
        void addBack(int);
        int getFront();
        void removeFront();
        void printQueue();
        
};

#endif
        

        
