import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], "r") as csvfile:  # OPens the CSV file
        reader = csv.DictReader(csvfile)
        for name in reader:  # Reads the dictionary into a list
            database.append(name)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as txt:  # OPens the txt file
        dna = txt.read()  # Reads the sequences into a string variable

    # TODO: Find longest match of each STR in DNA sequence
    AGATC = longest_match(dna, 'AGATC')  # The longest match of the STR - 'AGATC'
    AATG = longest_match(dna, 'AATG')  # The longest match of the STR - 'AATG'
    TATC = longest_match(dna, 'TATC')  # The longest match of the STR - 'TATC'

    # TODO: Check database for matching profiles
    for i in range(len(database)):  # Iterates through the database
        if database[i]['AGATC'] == str(AGATC) and database[i]['AATG'] == str(AATG) and database[i]['TATC'] == str(TATC):
            match = database[i]['name']
            is_matched = True  # If the matching profile is in the database then returns true
            break
        else:
            is_matched = False  # If there is no matching name then returns false

    # Prints if there is any matching name otherwise prints 'No match'
    if is_matched == False:
        print("No match")
    else:
        print(match)

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
