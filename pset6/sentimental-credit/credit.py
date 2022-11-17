import cs50
from math import trunc


def main():
    card = cs50.get_int("Number: ")

    # initialize count variables
    sum1 = int(0)
    sum2 = int(0)
    final = int(0)
    id1 = int(0)
    id2 = int(0)
    count = int(0)

    # initialize temporary card holder variable
    tmp = card
    tmp = trunc(tmp / 10)

    # loop through card to get sum 1
    while (tmp):
        if (tmp % 10 > 4):
            sum1 = trunc(sum1 + ((((tmp % 10) * 2) / 10) % 10))
            sum1 = trunc(sum1 + (((tmp % 10) * 2) % 10))
        else:
            sum1 = trunc(sum1 + (((tmp % 10) * 2) % 10))

        tmp = trunc(tmp / 100)

    # reset tmp card holder to get sum 2
    tmp = card

    # loop through card to get sum 2
    while (tmp):
        sum2 += (tmp % 10)
        tmp = trunc(tmp / 100)

    # add sum1 and sum2
    final = sum1 + sum2

    # reset tmp card holder one final time
    tmp = card

    # loop through tmp holder to count digits
    while (tmp):
        id2 = id1
        id1 = (tmp % 10)
        tmp = trunc(tmp / 10)
        count += 1

    # test for different card companies
    if (final % 10 == 0):
        if (id1 == 3 and (id2 == 4 or id2 == 7) and count == 15):
            print("AMEX")
        elif (id1 == 4 and (count == 13 or count == 16)):
            print("VISA")
        elif ((id1 == 5 and (id2 == 1 or id2 == 2 or id2 == 3 or id2 == 4 or id2 == 5) and count == 16)):
            print("MASTERCARD")
        else:
            print("INVALID")

    else:
        print("INVALID")


if __name__ == "__main__":
    main()

