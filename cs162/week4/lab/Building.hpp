/**************************************************************************************************
** Program Name:OSU Info System 
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Header file for the Building class. Contains all the member variables and function
                prototypes used by the class. Implementation for the class can be found in the
                Building.cpp file.
**************************************************************************************************/

#ifndef BUILDING_HPP
#define BUILDING_HPP
#include <string>

class Building {

    private: 
        std::string name;
        std::string address;
        long size;
        
    public:
        Building(); 
        Building(std::string, std::string, long);
        ~Building(); 
        std::string getName() const;
        void setName(std::string); 
        long getSize() const;
        void setSize(long); 
        std::string getAddress() const;
        void setAddress(std::string); 

};

#endif
