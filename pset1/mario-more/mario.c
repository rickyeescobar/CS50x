#include <cs50.h>
#include <stdio.h>

int ask(void)
{
    int height = 0;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    return height;
}

int main(void)
{

    int height = ask();
    // for each row
    for (int i = 0; i < height ; i++)
    {
        // for each column
        for (int p = 0; p > i - height + 1; p--)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            // print a brick
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < i + 1; k++)
        {
            // print second brick
            printf("#");
        }

        // move to next row
        printf("\n");
    }

}