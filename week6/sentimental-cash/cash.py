def main():
    print(coins(change_owed()))


def change_owed():
    while True:
        try:
            change = float(input("Enter amount of change owed: "))
        except ValueError:
            continue
        if change < 0:
            continue
        break
    return int(change*100)


def coins(owed):
    quarter = quarters(owed)
    owed = owed - quarter * 25
    dime = dimes(owed)
    owed = owed - dime * 10
    nickel = nickels(owed)
    owed = owed - nickel * 5
    return float(quarter+dime+nickel+owed)


def quarters(owed):
    return owed // 25


def dimes(owed):
    return owed // 10


def nickels(owed):
    return owed // 5


if __name__ == "__main__":
    main()