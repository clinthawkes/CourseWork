/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/04/2019
** Description: Header file for the Taxicab class. Three int variables are 
                created for the class functions to use. xCoord holds the 
                current location of x, yCoord stores the current location of y,
                and totalDistance is a running sum of all moves made by x and y.
                An explanation of each function, as well as their logic are 
                found in a separate file named Taxicab.cpp
*******************************************************************************/

#ifndef TAXICAB_HPP
#define TAXICAB_HPP

class Taxicab
{
    private:
        //variables created for use by class functions 
        int xCoord,
            yCoord,
            totalDistance;

    public:
        //constructor with int parameters  
        Taxicab(int, int);
        //default constructor    
        Taxicab();
        //returns value of xCoord as an int   
        int getXCoord();
        //returns value of yCoord as an int 
        int getYCoord();
        //returns value of totalDistance as an int   
        int getDistanceTraveled();
        //sets value of xCoord equal to int parameter 
        void moveX(int);
        //sets value of yCoord equal to int parameter 
        void moveY(int);

};
#endif
