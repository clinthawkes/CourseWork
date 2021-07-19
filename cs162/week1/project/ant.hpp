/*******************************************************************************    
** Program Name:Langton's Ant
** Name:        Clinton Hawkes
** Date:        04/08/2019
** Description: Header file for the Ant class. Contains all variables used
                by each class object, as well as the class function prototypes.
                Implementation of class functions is found in ant.cpp file.
*******************************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

class Ant{

    private:
        int antXCoord,              //list of all variables used by class
            antYCoord,
            numRow,
            numCol,
            numSteps,
            orientation;
        char** board; 

    public:
        Ant();                      //function prototypes of Ant class
        ~Ant(); 
        void setAntX(int);
        int getAntX();
        void setAntY(int);
        int getAntY();
        void setAntOrient(int);
        int getAntOrient();
        void setNumRow(int);
        int getNumRow();
        void setNumCol(int);
        int getNumCol();
        void setNumSteps(int);
        int getNumSteps();
        void createBoard();
        void printBoard(); 
        void changeOrient();
        void changeColor();
        void advance(); 


};

#endif
