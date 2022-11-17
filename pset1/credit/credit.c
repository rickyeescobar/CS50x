#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card = get_long("Number: ");

    int sum1 = 0, sum2 = 0, final = 0, id = 0, id2 = 0, count = 0;
    long tmp = card;


    tmp /= 10; // used to skip the first digit in the first loopthrough



    while (tmp)
    {
        // loops through every other digit starting with the second to last and does arithmetic
        // if sum of n * 2 is greater than 9, we need to separate the digits and add to sum1
        if (tmp % 10 > 4)
        {
            sum1 += ((((tmp % 10) * 2) / 10) % 10);
            //printf("%li\n", ((((tmp % 10)*2)/10)%10));
            sum1 += (((tmp % 10) * 2) % 10);
            //printf("%li\n", (((tmp % 10)*2)%10));
        }
        else
        {
            sum1 += (((tmp % 10) * 2) % 10);
            //printf("%li\n", (((tmp % 10)*2)%10));
        }
        //printf("%i\n", sum1);
        tmp /= 100;

    }

    tmp = card;

    while (tmp)
    {
        sum2 += (tmp % 10);
        //printf("%li\n", (tmp % 10));
        tmp /= 100;
    }

    //printf("%i\n", sum1);
    //printf("%i\n", sum2);

    // Adds two sums to check card validity
    final = sum1 + sum2;

    //printf("%i\n", final);

    // matches the first number of the card to identify card company
    tmp = card;
    while (tmp)
    {
        id2 = id;
        id = (tmp % 10);
        tmp /= 10;
        count++;
    }

    // tests final sum for validty using modulus
    if (final % 10 == 0)
    {
        if (id == 3 && (id2 == 4 || id2 == 7) && count == 15)
        {
            printf("AMEX\n");
        }
        else if (id == 4 && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else if (id == 5 && (id2 == 1 || id2 == 2 || id2 == 3 || id2 == 4 || id2 == 5) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }

}
