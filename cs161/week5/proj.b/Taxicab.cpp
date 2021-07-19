/******************************************************************************
 * Name:        Clinton Hawkes
 * Date:        February 02, 2019
 * Description: Includes all functions for the Taxicab class. The Taxicab 
 *              class is used to set xCoord and yCoord variables, change the
 *              variables using int parameters, return the values of the
 *              variables as an int, and track the net change made to the 
 *              variables by storing movements in the totalDistance variable.
 *****************************************************************************/

#include "Taxicab.hpp"
#include <cmath>

//constructor using parameters for xCoord and yCoord
Taxicab::Taxicab(int x, int y)
{
    xCoord = x;
    yCoord = y;
    totalDistance = 0;
}

//default constructor
Taxicab::Taxicab()
{
    xCoord = yCoord = totalDistance = 0;
}

//returns value of xCoord
int Taxicab::getXCoord()
{
    return xCoord;
}

//returns value of yCoord   
int Taxicab::getYCoord()
{
    return yCoord;
}

//returns value of totalDistance
int Taxicab::getDistanceTraveled()
{
    return totalDistance;
}


/*******************************************************************************
** Description: Takes in an int parameter for the number of spaces x needs to 
**              move and adds the number to the current xCoord variable. Then,
**              the absolute value of the input parameter is calculated and
**              added to the running total distance variable, totalDistance.
*******************************************************************************/
void Taxicab::moveX(int xMoves)
{
    xCoord += xMoves;
    totalDistance += std::abs(xMoves);
}


/*******************************************************************************
** Description: Takes in an int parameter for the number of spaces y needs to 
**              move and adds the number to the current yCoord variable. Then,
**              the absolute value of the input parameter is calculated and
**              added to the running total distance variable, totalDistance.
*******************************************************************************/
void Taxicab::moveY(int yMoves)
{
    yCoord += yMoves;
    totalDistance += std::abs(yMoves);
}


