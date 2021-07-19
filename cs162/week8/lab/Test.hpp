/**************************************************************************************************
** Program Name:Searching and Sorting
** Author:      Clinton Hawkes
** Date:        05/22/2019
** Description: Header file for the Test class. Contains the four vectors declarations and the
                function declarations. More details about these can be found in the Test.cpp file.
**************************************************************************************************/

#ifndef TEST_HPP
#define TEST_HPP
#include <vector>
#include <string>

class Test{

    private:
        std::vector<int> original;
        std::vector<int> beginning;
        std::vector<int> middle;
        std::vector<int> end;

    public:
        Test();
        int menu();
        void run();
        void readFiles();
        std::string simpleSearch(std::vector<int>, int);
        void sort(std::vector<int>&);
        std::string binarySearch(std::vector<int>, int);

};

#endif
