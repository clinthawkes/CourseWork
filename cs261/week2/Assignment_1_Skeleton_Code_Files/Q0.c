/* CS261- Assignment 1 - Q. 0*/
/* Name: Clinton Hawkes
 * Date: July 3, 2019
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){
  
     /*Print the value and address of the integer pointed to by iptr*/
    printf("The value of the integer in fooA is %d\n", *iptr);
    printf("The address of the integer in fooA is %p\n", iptr);
    
     /*Increment the value of the integer pointed to by iptr by 5*/
    *iptr += 5;

     /*Print the address of iptr itself*/
    printf("The address of iptr is %p\n", &iptr);

    /*Dummy variable, ignore the warning*/
   int c=5;  
}


void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/
    printf("The value of the integer in fooB is %d\n", *jptr);
    printf("The address of the integer in fooB is %p\n", jptr);

     /*Decrement the address by 1 pointed to by jptr using jptr */
    jptr--; 
    
     /*Print the address of jptr itself*/
    printf("The address of jptr is %p\n", &jptr); 
}


int main(){
    
    /*Declare an integer x and initialize it randomly to a value in [0,10] */
    srand(time(0)); 
    int x = rand()%11; 
    
    /*Print the value and address of x*/
    printf("The value of x is %d\n", x);
    printf("The address of x is %p\n", &x);
    
    /*Call fooA() with the address of x*/
    fooA(&x); 
    
    /*Print the value of x*/
    printf("The value of x is %d\n", x); 
    
    /* Yes, the value is changed. Since the address of the x variable is passed to the fooA function, */
    /* the function can use it as pointer. The function is able to change the value of the variable by */
    /* dereferencing the pointer. If the variable was passed by value, the value would have only been changed */
    /* for the copy of x in the function. */
    
    /*Call fooB() with the address of x*/
    fooB(&x); 
    
    /*Print the value and address of x*/
    printf("The value of x is %d\n", x);
    printf("The address of x is %p\n", &x);
    
    /* No, the value and address of x did not change. FooB changed the address that jptr was pointing to, */
    /* so anything done after changing that address would not have changed the x variable, because the */
    /* function was no longer able to reference the x variable. The address of x did not change, only the 
     * address where jptr was pointing. */
     
    return 0;
}


