/**************************************************************************************************
** Program Name:Linked List
** Author:      Clinton Hawkes
** Date:        05/05/2019
** Description: Header file for the Node class. This contains the member variable and function
                declarations for the class. More information about the functions below can be
                found in the Node.cpp file.
**************************************************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

class Node{

    private:
        int val;            //stores node value 
        Node* next;         //pointer storing next node's address
        Node* prev;         //pointer storing previous node's address

    public:
        Node();             //find more details in the Node.cpp file
        Node(int);
        int getVal() const;
        void setVal(int);
        Node* getNext() const;
        void setNext(Node*);
        Node* getPrev() const;
        void setPrev(Node*);
};

#endif
