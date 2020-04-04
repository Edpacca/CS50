import csv
import sys
from cs50 import SQL
from operator import itemgetter

# checks number of input arguments
if len(sys.argv) != 2:
    print("Error")
    sys.exit(1)

db = SQL("sqlite:///students.db")

# gets list of dictionaries from SQL query with argv[1]
students = db.execute(f"SELECT * FROM students WHERE house = \"{sys.argv[1]}\" ORDER BY last, first")

# already sorted so check if NULL then print
for i in range(len(students)):
    if students[i]['middle'] == None:
        print(f"{students[i]['first']} {students[i]['last']}, born {students[i]['birth']}")
    else:
        print(f"{students[i]['first']} {students[i]['middle']} {students[i]['last']}, born {students[i]['birth']}")

