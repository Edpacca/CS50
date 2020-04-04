import csv
import sys
import re

# Import data into an array from command line
# Define number of rows and columns for later use
data = list(csv.reader(open(sys.argv[1])))
rows = len(data)
cols = len(data[0])

# Open the sequence file and read the line into a string
sequence_file = (open(sys.argv[2], 'r'))
sequence = sequence_file.readline()

# Make an array for each code to count the max repeats
codes = [0] * (cols)
match = False


# Loop through the columns
for i in range(cols - 1):

    # Read length of first code in data
    check_code = data[0][i+1]
    code_len = int(len(data[0][i+1]))

    # For each character in the sequence check if its the start of the codon
    for x in range(int(len(sequence))):

        # Set counters to 0
        counter = 0
        y = 0
        # While there's a match, add counter and move onto next sequence and check again
        while (sequence[x + (y * code_len): (x + (code_len * (y + 1)))]) == check_code:
            counter += 1
            y += 1

        # After counting number of successive sequences, check if its the longest repeat
        # If so read it into the array at the corresponding location to the check code in data array
        if counter > codes[i+1]:
            codes[i+1] = counter


# Comparing the code repeat array with the data
for i in range(1, rows):
    j = 1
    # If matched in first column, check next column until no match
    while j <= cols - 1 and (int(data[i][j]) == int(codes[j])):
        if j < cols - 1:
            j += 1
        # If all columns matched then print name
        elif j == cols - 1:
            print(data[i][0])
            match = True
            break

# If no one matched then print "No Match"
if not match:
    print("No Match")
