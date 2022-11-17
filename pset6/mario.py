def main():
    for i in range(get_int()):
        print("?",end="")
    print("")

    print("?" * get_int())

def get_int():
    while True:
        try:
            n = int(input("Length: "))
            return n
        except:
            print("use a valid int")





if __name__ == "__main__":
    main()