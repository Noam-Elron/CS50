def main():
    height = get_height()
    print_pyramid(height)


def get_height():
    while True:
        try:
            h = int(input("Enter height: "))
        except ValueError:
            print("Please input digit ")
            continue
        if (0 < h < 9):
            return h


def print_pyramid(height):
    for i in range(1, height+1):
        print(" " * (height-i) + "#" * i)
    return


if __name__ == "__main__":
    main()