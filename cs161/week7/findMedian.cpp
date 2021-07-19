/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/14/2019
** Description: File contains the findMedian function. The function takes in an
                array of ints for one parameter and the size of the array as an
                int for the second parameter. The array of ints is sorted and 
                the median of the list is calculated. The median is returned as
                a double.
*******************************************************************************/
#include <algorithm>

//function finds median of input array and is explained in the description
double findMedian(int inArr[], int size) {
    
    //sorts the array of ints in ascending order 
    std::sort(inArr, inArr + size);

    //calculates median if the size of the array is even and returns it
    if (size%2 == 0)
        return (inArr[size/2] + inArr[(size/2)-1])/2.0;
    
    //calculates median if the size of the array is odd and returns it
    else
        return (double) inArr[((size-1)/2)];
}
