def main():
    # get user input
    inpt = input("Text: ")

    # call functions that count letters, words, and sentences
    letter_count = count_letters(inpt)
    word_count = count_words(inpt)
    sentence_count = count_sentences(inpt)

    # impliment Coleman-Liau index formula
    index = (0.0588 * (letter_count / word_count * 100) - 0.296 *
             (sentence_count / word_count * 100) - 15.8)

    # format index into printable format
    new_index = round(index)

    # print out result
    # print results greater than grade 16
    if (new_index >= 16):
        print("Grade 16+")
        return 0

    # print results less than grade 1
    if (new_index < 1):
        print("Before Grade 1")
        return 0

    # print all other grades in between
    else:
        print(f"Grade {new_index}")
        return 0


# function to count letters in text input
def count_letters(text):
    letter_count = 0
    i = 0
    while (len(text) > i):
        if (text[i].isalpha()):
            letter_count += 1
        i += 1

    return letter_count

# function to count words in text input


def count_words(text):
    word_count = 0
    i = 0
    while (len(text) > i):
        if (text[i] == ' '):
            word_count += 1
        i += 1

    word_count += 1
    return word_count

# function to count sentences in text input


def count_sentences(text):

    sentence_count = 0
    i = 0
    while (len(text) > i):
        if (text[i] == '.' or text[i] == '?' or text[i] == '!'):
            sentence_count += 1
        i += 1

    return sentence_count


if __name__ == "__main__":
    main()