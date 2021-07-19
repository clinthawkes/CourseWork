#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {

    double a = 2.0;
    double b = 3.0;
    double c = 4.0;
    double s = (a + b + c) / 2;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));

    printf("The length of side a is %g \n", a);
    printf("The length of side b is %g \n", b);
    printf("The length of side c is %g \n", c);
    printf("The area of the triangle is %g \n", area);

    return 0;
}