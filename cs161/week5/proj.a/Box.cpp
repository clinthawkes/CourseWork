/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/03/2019
** Description: File contains the logic for all the functions of the Box class.
                The Box class has 3 variables(height, width, and length) that
                are able to be changed using a setter function for each 
                variable with an parameter input. There are two other functions
                that return a double after using the three variable to 
                calculate the volume or the surface area.
*******************************************************************************/

#include "Box.hpp"

//default constructor  
Box::Box()
{   
    height = width = length = 1;
}

//constructor with parameter inputs for height, width and length
Box::Box(double h, double w, double l)
{
    height = h;
    width = w;
    length = l;
}

//height variable setter using double parameter
void Box::setHeight(double h)
{
    height = h;
}

//width variable setter using double parameter
void Box::setWidth(double w)
{
    width = w;
}

//length variable setter using double parameter
void Box::setLength(double l)
{
    length = l;
}


/*******************************************************************************
** Description: Calculates the volume of the rectangle(box) using the height,
**              width and length variables, and then returns the value as a 
**              double.
*******************************************************************************/
double Box::calcVolume()
{
    return height * width * length;
}


/*******************************************************************************
** Description: Calculates the surface area of the rectangle(box) using the
**              height, width and length variables, and then returns the value
**              as a double.
*******************************************************************************/
double Box::calcSurfaceArea()
{
    return 2 * (height * width + width * length + length * height);
}

