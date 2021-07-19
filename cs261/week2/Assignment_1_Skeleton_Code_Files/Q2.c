/* CS261- Assignment 1 - Q.2*/
/* Name:
 * Date:
 * Solution description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    int* temp = a;
    a = b;
    b = temp;
    
    /*Decrement the value of integer variable c*/
    c--; 
    
    /*Return c*/
    return c; 
}

int main(){
    
    srand(time(0)); 
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand()%11, 
        y = rand()%11, 
        z = rand()%11;

    /*Print the values of x, y and z*/
    printf("The value of x is %d\n", x); 
    printf("The value of y is %d\n", y); 
    printf("The value of z is %d\n", z); 
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    foo(&x, &y, z); 
    
    /*Print the values of x, y and z*/
    printf("The value of x is %d\n", x); 
    printf("The value of y is %d\n", y); 
    printf("The value of z is %d\n", z); 
    
    /*Print the value returned by foo*/
    printf("The value returned from foo is %d\n", foo(&x, &y, z)); 
    
    return 0;
}
    
/*  Yes, the return value is different than z. Z was passed to the foo function by value. This means
 *  that anything done to the variable inside the function was actually done to a copy of the variable.
 *  After the function returns to the calling function (main), the variable is unchanged. The function
 *  can, however, return the changed value of the local copy if the function is set to return a value. The 
 *  function can take in a variable by value, make changes to the local copy of the variable and then 
 *  return the value of the local variable to the calling function. This is why the returning value is
 *  1 less than the value of z.*/    

/*  No, the values of the x and y integers do not change. The reason is because we did not dereference
 *  the pointers to swap the values of the variables. What we did was take the local pointer variables
 *  a and b and change what addresses they point to. This had no effect on the integer variables x and y.
 *  All it did was make the a pointer reference integer y, and the b pointer reference integer x. This 
 *  only matters inside the function. After we return to the main function, the integers remain unchanged. 
 *  If we were to dereference the pointers and swap the values of x and y, the values of the x and y
 *  variables would have been changed after we returned to the main function. We were told not to do this
 *  though. */

