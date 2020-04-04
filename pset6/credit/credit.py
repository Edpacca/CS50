from cs50 import get_int, get_string


def main():

    # gets the credit card number
    credit_str = get_credit()

    # convert number to list of integers from geekforgeeks.org
    credit_num = [int(x) for x in str(credit_str)]
    digit = int(len(credit_num))
    sum2 = 0    # sum of digits x 2 in sum1
    sum3 = 0    # sum of other digits

    while digit > 0:

        # sum of every other digit doubled, starting second to last
        if (digit - 2 >= 0):
            sum1 = str(2 * credit_num[digit - 2])

            # sums up the digits at each iteration to sum2
            for j in sum1:
                sum2 += int(j)

        # sum3 adds up the other digits not in sum1
        sum3 += (credit_num[digit - 1])
        digit -= 2

    # check if valid credit card then checks type
    if ((sum2 + sum3) % 10 == 0):
        if (len(credit_num) == 15 and ('34' or '37' == credit_str[:2])):
            print("AMEX\n", end="")
        elif (len(credit_num) == 16 and (50 < int(credit_str[:2]) < 56)):
            print("MASTERCARD\n", end="")
        elif (13 or 16 == len(credit_num) and credit_num[0] == 4):
            print("VISA\n", end="")
    # else prints invalid
    else:
        print("INVALID\n", end="")


def get_credit():
    n = get_string("Number: ")
    if len(n) > 0:
        return n


main()
