/*************************************************************************************
 * Name:        Clinton Hawkes
 * Date:        January 27, 2019
 * Description: Function takes in three integers by reference and sorts their 
 *              values in ascending order.
 ************************************************************************************/
/*
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void smallSort (int&, int&, int&);


int main()
{
    int first,
        second,
        third;

    cout << "Please enter three integers to sort." << endl;
    cin >> first >> second >> third;

    smallSort(first, second, third);

    cout << first << ", " << second << ", " << third << endl;
    
    return 0; 
}
*/

/*************************************************************************************
 * Description: Function takes in three integers by reference and sorts thier
 *              values in ascending order.
 ************************************************************************************/

void smallSort (int &num1, int &num2, int &num3)
{
    int temp;           //declares int variable 

    if (num1 > num2)    //if num1 is more than num2, values are swapped
    {   temp = num1;
        num1 = num2;
        num2 = temp;}
    
    if (num1 > num3)    //if num1 is more than num3, values are swapped
    {   temp = num1;    //now we know num1 is the smallest of the three
        num1 = num3;
        num3 = temp;}
    
    if (num2 > num3)    //if num2 is more than num3, values are swapped
    {   temp = num2;    
        num2 = num3;    //we know num1 is the smallest, so we just have
        num3 = temp;}   //to sort num2 and num3
}
