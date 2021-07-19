/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/03/2019
** Description  Header file for Box class. Creates three double variables for
                use by class functions. Class function prototypes are listed 
                below and the logic of the functions are contained in a 
                separate file named Box.cpp
*******************************************************************************/

#ifndef BOX_HPP
#define BOX_HPP

class Box
{
    private:
        //variables for Box class
        double height, width, length;

    public:
        //function prototypes for Box class. Explanation of each function is 
        //contained in the Box.cpp file with each function's logic.
        
        //constructor
        Box(double, double, double); 
        //constructor    
        Box(); 
        //height setter 
        void setHeight(double);
        //width setter   
        void setWidth(double);
        //length setter  
        void setLength(double);
        //volume calculator 
        double calcVolume();
        //surface area calculator 
        double calcSurfaceArea();

};
#endif
