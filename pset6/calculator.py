try:
    x = int(input("x: "))
except:
    print("use a valid int")
try:
    y = int(input("y: "))
except:
    print("use a valid int integer")

z = x / y
print(f"{z:.50f}")