import sys
import csv




# TODO: Read database file into a variable
database = []
with open("databases/large.csv", "r") as csvfile:
        reader = csv.DictReader(csvfile)
        for name in reader:
            database.append(name)

with open("sequences/18.txt", "r") as txt:
        dna = txt.read()



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

AGATC = longest_match(dna, 'AGATC')
AATG = longest_match(dna, 'AATG')
TATC = longest_match(dna, 'TATC')
TTTTTTCT = longest_match(dna, 'TTTTTTCT')
TCTAG = longest_match(dna, 'TCTAG')
GATA = longest_match(dna, 'GATA')
GATA = longest_match(dna, 'GATA')
GATA = longest_match(dna, 'TCTG')
for i in range (len(database)):
    if database[i]['AGATC'] == str(AGATC) and database[i]['AATG'] == str(AATG) and database[i]['TATC'] == str(TATC) and database[i]['TTTTTTCT'] == str(TTTTTTCT) and database[i]['TCTAG'] == str(TCTAG) and database[i]['GATA'] == str(GATA) and database[i]['GAAA'] == str(GAAA) and database[i]['TCTG'] == str(TCTG):
        match = database[i]['name']
        ismatched = True
        break
    else:
        ismatched = False

if ismatched == False:
    print("nomatcg:")
else:
    print(match)
    print()
