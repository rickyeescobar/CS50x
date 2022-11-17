#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string inpt = get_string("What is your first name?: ");
    printf("hello, %s\n", inpt);
}