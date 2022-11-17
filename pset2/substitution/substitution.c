#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    char ALPHA[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    // GET KEY
        // key = argv, then copied to check_duplicates

    // VALIDATE KEY
        // process input argument key (case insensitive)

        // if no command line args or more than one, print error and return "1"
    if (! argv[1] || argv[3] == false)
    {
        printf("./substitution key\n");
        return 1;
    }

        // if key is invalid print error message and return "1"
            // not 26 chars

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
            // containing non alphabetical characters

    int i = 0;
    while (strlen(argv[1]) > i )
    {
        if (! isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        i++;
    }
            // containing dupicates
                // create array to check for duplicates against
    i = 0;
    char check_duplicates[26] = {};
    while (strlen(argv[1]) > i )
    {
        check_duplicates[i] = tolower(argv[1][i]);
        i++;
    }
                // Check for duplicates with 2 for loops and show duplicate letter
    for (i= 0; i < 26; i++)
    {
        int duplicate_count = 0;

        for (int j = 0; j < 26; j++)
        {
            if (check_duplicates[i] == tolower(argv[1][j]))
            {
                duplicate_count ++;
            }
            if (duplicate_count == 2)
            {
                printf("%c is a duplicate value in the key\n",check_duplicates[i]);
                return 1;
            }
        }
    }

    // GET PLAINTEXT
        // 1. output plaintext: (no newline \n) then 2. prompt user for string of plaintext (get_string)

    string plaintext = get_string("plaintext:  ");

    printf("ciphertext: ");

    // ENCIPHER
        // program must preserve case

    i = 0;
    while (strlen(plaintext) > i)
    {
        int counter = 0;

        if (plaintext[i] == '\'')
        {
            printf("'");
            i++;
        }

        while ( tolower(plaintext[i]) != ALPHA[counter] )
        {
            counter++;
        }

    // PRINT CIPHERTEXT
        // output "ciphertext: (without newline) then plaintext's ciphertext

        if (isupper(plaintext[i]))
        {
            printf("%c", toupper(check_duplicates[counter]));
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", check_duplicates[counter]);
        }
        else
        {
            printf("%c", plaintext[i]);
        }

        i++;
    }

        // print newline and exit by returning 0 from main
    printf("\n");
    return 0;
}