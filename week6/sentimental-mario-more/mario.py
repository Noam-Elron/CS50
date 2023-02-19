# TODO
while True:
    try:
        height = int(input("Enter height: "))
        if height > 0 and height <= 8:
            break
    except ValueError:
        continue

for i in range(1, height+1):
    print(" " * (height-i) + "#" * i + "  " + "#" * i)
