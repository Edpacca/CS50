from cs50 import get_int

# main function gets the int from user via get_positive_int
# prints required pyramid


def main():
    h = get_positive_int()
    w = 1
    for i in range(h):
        print(" " * (h - w), end="")
        print("#" * w, '', "#" * w)
        w += 1

# get positive int function returns if number is between 1 and 9


def get_positive_int():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            return n


main()
