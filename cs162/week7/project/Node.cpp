/**************************************************************************************************
** Program Name:Fantasy Combat   
** Author:      Clinton Hawkes
** Date:        05/22/2019
** Description: Implementation file for the Node class. This node class is basically just used to
                store information and act as the building blocks of the LinkedList class. This
                class has three member variables and getter/setter functions to go with them. That
                is is. Functions can be found below.
**************************************************************************************************/

#include "Node.hpp"

//default constructor 
Node::Node(){
    
    setFighter(nullptr);
    setNext(nullptr);
    setPrev(nullptr);
}

//constructor with one arguement for the val variable
Node::Node(Character* person){

    setFighter(person);          //sets val equal to passed parameter
    setNext(nullptr);
    setPrev(nullptr);
}

//getter function for the val variable
Character* Node::getFighter() const{

    return fighter;
}

//setter function for the val variable      
void Node::setFighter(Character* person){

    fighter = person;
}

//getter function for the next variable
Node* Node::getNext() const{

    return next;
}

//setter function for the next variable
void Node::setNext(Node* n){

    next = n;
}

//getter function for the prev variable
Node* Node::getPrev() const{

    return prev;
}

//setter function for the prev variable
void Node::setPrev(Node* p){

    prev = p;
}
