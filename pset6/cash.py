# we got quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).

def main():
    owed = get_owed()
    coins = calc_coins(owed)
    print(coins)


def get_owed():
    while True:
        try:
            dollars = float(input('Change owed: '))
        except ValueError:
            pass
        else:
            if dollars > 0:
                return dollars


def calc_coins(owed):
    cents = round(owed * 100)
    quarters = int(cents / 25)
    cents %= 25
    dimes = int(cents / 10)
    cents %= 10
    nickels = int(cents / 5)
    pennies = cents % 5
    coins = quarters + dimes + nickels + pennies

    return coins


if __name__ == '__main__':
    main()
