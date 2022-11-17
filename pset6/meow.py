def meow():
    print("Meow")

def main():
    try:
        for i in range(int(input("how many times should I meow? "))):
            meow()
    except:
        print("invalid input")

if __name__ == "__main__":
    main()