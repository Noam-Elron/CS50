import csv
import sys


def main():

    # Check for command-line usage

    if len(sys.argv) != 3:
        print("Invalid CLI-Input: First input should include name of CSV Data containing individual data and second input should include the text file that contains sequences to search for.")
        sys.exit()

    # Read database file into a variable

    csvfile = open(sys.argv[1], "r")
    reader = csv.DictReader(csvfile)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as s_file:
        sequences = s_file.read()

    # Find longest match of each STR in DNA sequence

    runs = {}
    # Subsequence takes on the value of every sequence fieldname in the csv file (first field is name field so skipping over it).
    for subsequence in (reader.fieldnames)[1:]:
        # Creating a new key value pair in runs. Key is the current subsequence with the value being the calculation done by function longest_match( counts largest concurrent subsequences in the sequences file )
        runs[subsequence] = longest_match(sequences, subsequence)

    # Check database for matching profiles
    match = database_match(reader, runs)
    if (match != None):
        print(match)
    else:
        print("No match")
    # Close csvfile to confrom to standard python practices. Python usually takes care of this automatically but best to make sure.
    csvfile.close()
    return 0


def database_match(csvfile, sub_counts):
    for row in csvfile:
        sub_match = 0
        for subsequence in (csvfile.fieldnames)[1:]:
            # If value of sequence in database of row(person[i]) != value of concurrent sequence in sub_counts then it cant be match, thus breaking out of current loop removes the redundancy of checking next sequences in someone whos already not a match and skips to the next row.
            if int(row[subsequence]) != int(sub_counts[subsequence]):
                break
            # If concurrency is a match then former isnt activated and thus sub_match += 1 gets called because current iteration continues
            sub_match += 1
            if sub_match == len(sub_counts):
                return row['name']
    return None


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


if __name__ == "__main__":
    main()
