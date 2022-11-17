import csv
import sys


def main():

    # TODO: Check for command-line usage

    # test for 2 command- line arguments
    if len(sys.argv) != 3:
        print("Usage: dna.py [CSV file] [DNA sequence file]")
        return 1
    elif (not sys.argv[1].endswith(".csv")):
        print("Must use CSV file in correct position")
        return 1
    elif (not sys.argv[2].endswith(".txt")):
        print("Must use TXT file in correct position")
        return 1

    # TODO: Read database file into a variable  - people_data[i]["name"]
    db_file = sys.argv[1]
    dna_file = sys.argv[2]

    # find STR sequences for use in program
    with open(db_file, "r") as file:
        reader = csv.reader(file)
        sequences = next(reader)

    sequences = sequences[1:]
    # print(sequences)

    # create dictionary that keeps track of sequence count
    sequence_count = {}
    for s in sequences:
        sequence_count[s] = 0

    # read database into dictionary
    people_data = {}

    with open(db_file, "r") as file:
        dctreader = csv.DictReader(file)
        i = 0
        for row in dctreader:
            people_data[i] = row
            i += 1

    # TODO: Read DNA sequence file into a variable  - dna_strand
    with open(dna_file, "r") as file:
        dna_strand = file.read()

    # TODO: Find longest match of each STR in DNA sequence

    for s in sequences:
        longest = longest_match(dna_strand, s)
        sequence_count[s] = longest

    # TODO: Check database for matching profiles
    matched = ""

    for person in people_data:
        match = 0
        for sequence, count in sequence_count.items():
            if int(people_data[person][sequence]) == int(count):
                match += 1
            if match == len(sequences):
                matched = (people_data[person]["name"])

    if (matched):
        print(matched)
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
