
def main():
    credit_card = int(input("Enter credit card number: "))
    card_dig = [int(x) for x in str(credit_card)]  # Could technically just change input to str and then from str to list but meh.
    #print(f"Valid?: {valid(card_dig)}")
    if valid(card_dig):
        company(len(card_dig), str(card_dig[0]), str(card_dig[1]))
        return
    print("INVALID")
    return


def valid(card_number):
    if len(card_number) not in [13, 15, 16] or not (algo(card_number)):
        return False
    return True


def algo(card_number):
    summed = 0

    # Adding numbers that werent multiplied by 2
    unmul_digits = card_number[-1::-2]
    # Creating a list slice starting from second to last digit of original and continuing with every other number.

    second_digits = card_number[-2::-2]
    second_digits = [x * 2 for x in second_digits]
    # If a number is greater than 10 than it simply adds the second digit (x%10) with the first digit (x//10), otherwise it simply adds the digit + 0

    summed = sum([(x % 10 + x//10) for x in second_digits])
    summed += sum(unmul_digits)
    #print(summed)
    if summed % 10 == 0:
        return True
    return False


def company(card_len, dig1, dig2):
    #print(card_len, dig1 + dig2)
    if card_len == 15 and (dig1 + dig2 == "34" or dig1 + dig2 == "37"):
        print("AMEX")
    elif card_len == 16 and (int(dig1 + dig2) in range(51, 56)):
        print("MASTERCARD")
    elif (card_len == 13 or card_len == 16) and (dig1 == "4"):
        print("VISA")
    else:
        print("INVALID")
    return


if __name__ == "__main__":
    main()