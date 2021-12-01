import cs50


def main():
    number = cs50.get_int('Number: ')
    number_str = str(number)

    checksum = calc_checksum(number_str)
    card_type = get_card_type(number_str, checksum)

    print(card_type)


def calc_checksum(number_str):
    reversed_str = number_str[::-1]

    evens = reversed_str[::2]
    evens_sum = sum(int(digit) for digit in evens)

    odds_sum = 0
    odds = reversed_str[1::2]

    for s in odds:
        num = int(s)
        odds_sum += get_sum_of_digits(num * 2)

    return evens_sum + odds_sum


def get_sum_of_digits(num):
    if num < 9:
        return num

    return int(num / 10) + num % 10


def get_card_type(number_str, checksum):
    last_digit = checksum % 10

    if last_digit != 0:
        return 'INVALID'

    card_id = int(number_str[:2])
    length = len(number_str)
    
    if length == 15 and card_id in [34, 37]:
        return 'AMEX'

    if length == 16 and card_id in range(51, 56):
        return 'MASTERCARD'

    if length in [13, 16] and number_str[0] == '4':
        return 'VISA'

    return 'INVALID'


if __name__ == '__main__':
    main()
