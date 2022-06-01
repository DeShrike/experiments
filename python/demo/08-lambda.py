def main():
    lijst = ["maandag", "dinsdag", "woensdag", "donderdag", "vrijdag", "zaterdag", "zondag"]

    lijst2 = [ day for day in sorted(lijst, key=lambda value: ord(value[2]), reverse = True) ]
    print(lijst2)
    
    lijst3 = sorted(lijst, key=lambda x: x[-4])
    print(lijst3)

    mysortkey = lambda value: len(value)
    lijst4 = [ "".join(reversed(day)) for day in sorted(lijst, key=mysortkey) ]
    print(lijst4)


if __name__ == "__main__":
    main()
