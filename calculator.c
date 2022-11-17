#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // prompt user for x
    int x = get_int("x: ");

    // prompt user for y
    int y = get_int("y: ");

    // Divide x by z
    float z = (float) x / (float) y;

    // print x + y
    printf("%.50f\n", z);
}