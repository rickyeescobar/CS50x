#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


// function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

// main function
int main(void)
{
    // get user input
    string input = get_string("Text: ");

    //call functions that count letters, words, and sentences
    int letter_count = count_letters(input);
    int word_count = count_words(input);
    int sentence_count = count_sentences(input);

    // impliment Coleman-Liau index formula
    double index = 0.0588 * ((float)letter_count / (float) word_count * 100) - 0.296 *
    ((float)sentence_count / (float) word_count * 100) - 15.8;

    // format index into printable format
    int new_index = (int) round(index);

    // print out result
        // print results greater than grade 16
    if (new_index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
        // print results less than grade 1
    if (new_index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
        // print all other grades in between
    else
    {
        printf("Grade %i\n", new_index);
        return 0;
    }
}

// function to count letters in text input
int count_letters(string text)
{
    int letter_count = 0;
    int i = 0;
    while (strlen(text) > i)
    {
        if (isalpha(text[i]))
        {
            letter_count++;
        }
        i++;
    }
    return letter_count;
}
// function to count words in text input
int count_words(string text)
{
    int word_count = 0;
    int i = 0;
    while (strlen(text) > i)
    {
        if (text[i] == ' ')
        {
            word_count++;
        }
        i++;
    }
    word_count++;
    return word_count;
}
// function to count sentences in text input
int count_sentences(string text)
{
    int sentence_count = 0;
    int i = 0;
    while (strlen(text) > i)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence_count++;
        }
        i++;
    }
    return sentence_count;
}