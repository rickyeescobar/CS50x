#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int get_key(string key);
string encipher(string plaintext, int key);

int main(int argc, string argv[])
{

    if (! argv[1] || (bool) argv[2] == true)
    {
        printf("./caesar key\n");
        return 1;
    }
    // get command line argument key
    int key = get_key(argv[1]);

    // check for correct positive integer
    if (key == -1)
    {
        printf("Key must be positive");
    }
    if (key == -2)
    {
        printf("./caesar key\n");
        return 1;
    }

    // prompts user for the string of plaintext
    string plaintext = get_string("plaintext:  ");
    // prints out the title line for ciphertext
    printf("ciphertext: ");
    // enciphers and prints out the ciphertext
    string ciphertext = encipher(plaintext, key);

}
// get the key and test it to the required specs

int get_key(string key)
{
    int new_key;
    int i = 0;
    while (strlen(key) > i)
    {
        if (! isdigit(key[i]))
        {
            return -2;
        }
        if (key[i] < 0)
        {
            return -1;
        }
        i++;
    }
    new_key = atoi(key);
    return new_key;
}

// loop through the plaintext and encipher it using the formula and key
string encipher(string plaintext, int key)
{

    int i = 0;
    string ciphertext = NULL;
    while (strlen(plaintext) > i)
    {
        // for if the letter is uppercase
        if isupper(plaintext[i])
        {
            printf("%c", (plaintext[i] - 65  + key) % 26 + 65);
        }
        // for if the letter is lowercase
        else if islower(plaintext[i])
        {
            printf("%c", (plaintext[i] - 97  + key) % 26 + 97);
        }
        // for if the letter is a space or anything else
        else
        {
            printf("%c", plaintext[i]);
        }
        i++;
    }

    // print out the final line
    printf("\n");
    return ciphertext;
}