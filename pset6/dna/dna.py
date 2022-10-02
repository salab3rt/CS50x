import csv
import sys
import copy


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py data.csv sequence.txt')

    # TODO: Read database file into a variable
    DNA_db = []
    strs = []
    with open(sys.argv[1], 'r') as datab:    # Open file refered on argv[1]
        name_reader = csv.DictReader(datab)  # Read file with .DictReader
        for name in name_reader:
            name['name'] = name['name']
            DNA_db.append(name)     # Save file in a list, so we end up with a list of dictionaries
    #print ('PERSON: --->', DNA_db)

    # Get the str (short tandem repetitions) from the file itself,
    # intead of hardcoding them to a variable
    with open(sys.argv[1], 'r') as header:   # Open argv[1] file once again
        head_reader = csv.reader(header)    # Read with .reader
        strs = next(head_reader)    # Read the first line in a list
        strs.remove('name')     # Remove the 'name' key
    #print('\nSUBSUBSEQUENCES  --->   ', strs, '\n')

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as sequence_f:   # Open file refered on argv[2]
        sequence = sequence_f.read()    # Read file content to variable
    #print(sequence)

    # TODO: Find longest match of each STR in DNA sequence
    count = {}
    for i in range(len(strs)):
        # Longest match_returns funtions the value of repetitions of a given substring in a string
        check_long = longest_match(sequence, strs[i])   # Pass to longest_match, sequence and a str from our strs[] list
        # Update the result in a counts dicionary, where the key is the str we passed, and the return value
        count.update({strs[i]: check_long})
    #print('SUBSEQUENCE COUNT --->   ', count, '\n')

    # TODO: Check database for matching profiles
    match = find_match(DNA_db, count)
    print(DNA_db[match]['name'])
    header.close()
    datab.close()
    sequence_f.close()
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


def find_match(DNAdb, count):

    # Could have used  list comprehension + list comprehension as in:
    # https://www.geeksforgeeks.org/python-remove-key-from-dictionary-list/
    # DNA_dbcopy = [{key: int(value) for key, value in sub.items() if key != 'name'} for sub in DNA_db]
    # Since i could not grasp in its entirety, opted to use deepcopy

    DNAdb_copy = copy.deepcopy(DNAdb)

    # Delete 'name' key from DNAdb copy, to compare with count
    del_key = 'name'    # Set a key to delete
    for key in DNAdb_copy:
        if del_key in key:
            del key[del_key]

    i = 0   # Keep track of each loop iteration
    for dict in DNAdb_copy:  # For each dict in DNAdb_copy
        for key, value in dict.items():
            dict[key] = int(value)   # For each key value, swap it for its integer value
            if dict == count:   # On match
                return i    # Return i for the list index
        i += 1
    print('No match.')
    exit()


if __name__ == '__main__':
    main()
