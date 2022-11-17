import cs50

# start loop to get the right integer value
while True:
    height = cs50.get_int("Height: ")
    if height > 0 and height < 9:
        break

# loop through the range and print the bricks
for i in range(height):
    print(" " * ((height - 1) - i) + "#" * (i + 1) + "  " + "#" * (i + 1), sep="")
