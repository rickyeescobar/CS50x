#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string("Name: ");

    int length = string_length(name);
    printf("%i\n", length);


}

