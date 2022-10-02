# TODO
import re


def main():

    try:
        card_num = input('Card number? ')
        check(card_num)
    except:
        print('INVALID')


def check(card_num):

    cardbrand = {  # Store credit card regular expressions inside a dictionary
        'VISA': '^[4]\d{12}$|^[4]\d{15}$',   # Visa regular expression
        'AMEX': '^34\d{13}$|^37\d{13}$',  # Amex regular expression
        'MASTERCARD': '^5[1-5]\d{14}$',  # Mastercard regular expression
    }

    card_num = re.sub("[ ]|[-]", '', card_num)  # Remove card number 'spaces' and '-'

    for key in cardbrand:
        compiler = re.compile(cardbrand[key])
        check_valid = re.match(compiler, card_num)  # Check for match according to cards regular expressions

        if check_valid != None:  # Matches
            checksum(card_num)  # Run Luhn’s Algorithm
            print(key)  # If valid checksum proceed to print the card brand
            return (0)
    else:
        exit(1)


def checksum(card_num):
    sum1 = 0
    sum2 = 0

    for x in range((len(card_num) - 2), -1, -2):    # Iterate through every other digit starting from second to last
        z = (int(card_num[x]) * 2)    # Multiply * 2 each digit
        sum1 += int(z % 10) + int(z / 10)   # Sum each digit from z

    for y in range((len(card_num) - 1), -1, -2):    # Iterate through every other digit starting from last
        sum2 += int(card_num[y])    # Sum the digits

    if ((sum1 + sum2) % 10) == 0:   # Check if sum1 + sum2 ends with 0
        return (0)
    else:
        exit(1)


if __name__ == '__main__':
    main()