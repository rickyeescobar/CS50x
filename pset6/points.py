from cs50 import get_int

points = get_int("how many points did you lose?")

if points < 2:
    print("you lost fewer points than me")
elif points > 2:
    print("you lost more points than me.")
else:
    print("you lost the same number of points as me")