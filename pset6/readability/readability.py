from cs50 import get_string
from collections import Counter

# get string from user
text = get_string("Text: ")
# applies counter funciton to get punctuation
counter = Counter(text)
words = counter[' '] + 1
stops = counter['.'] + counter['!'] + counter['?']
# iterates through and counts alpha characters
letters = 0
for i in text:
    if (i.isalpha()) == True:
        letters += 1

# calculates index
index = 0.0588 * (100 * (letters / words)) - 0.296 * (100 * (stops / words)) - 15.8

# checks grade
if (1 <= index < 16):
    print(f"Grade {round(index)}")
elif (index >= 16):
    print("Grade 16+")
elif (index < 1):
    print("Before Grade 1")