from cs50 import get_string

people = {
    "Carter": "+1-617-495-100",
    "David": "+1-949-468-2750"
}

name = get_string("name: ")
if name in people:
    number = people[name]
    print(f"Number: {people[name]}")
