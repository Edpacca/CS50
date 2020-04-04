import csv
import sys
from cs50 import SQL

# checks number of input arguments
if len(sys.argv) != 2:
    print("Error")
    sys.exit(1)

db = SQL("sqlite:///students.db")

# reads data into a 2D list
data = list(csv.reader(open(sys.argv[1])))

# iterates through data checks for whitespace
for i in range(1, len(data)):

    # if valid splits full name into sub list
    if not (str(data[i][0]).isspace()):
        fullname = data[i][0].split()

        # checks len of fullname and puts values in appropriate column
        # inserts values into the table
        if len(fullname) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       fullname[0], fullname[1], fullname[2], data[i][1], data[i][2])

        elif len(fullname) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)",
                       fullname[0], fullname[1], data[i][1], data[i][2])