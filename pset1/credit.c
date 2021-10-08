#include <cs50.h>
#include <math.h>
#include <stdio.h>

int get_card_id(long);
int get_digits_count(long);
int get_first_digits(long, int);
int get_sum_of_digits(int);

bool is_amex(long);
bool is_mastercard(long);
bool is_visa(long);

int main(void) {
    long number = get_long("Number: ");
    long temp = number;
    int evens_sum = 0;
    int odds_sum = 0;
    int last;
    int step = 0;

    do {
        step++;
        last = temp % 10;
        temp = temp / 10;

        if (step % 2 == 0) {
            evens_sum += get_sum_of_digits(last * 2);
        } else {
            odds_sum += last;
        }
    } while (temp > 0);

    int result_sum = evens_sum + odds_sum;

    if (result_sum % 10 != 0) {
        printf("INVALID\n");
    } else if (is_amex(number)) {
        printf("AMEX\n");
    } else if (is_mastercard(number)) {
        printf("MASTERCARD\n");
    } else if (is_visa(number)) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }
}

int get_sum_of_digits(int number) {
    if (number < 10) {
        return number;
    }

    return (number / 10) + (number % 10);
}

int get_digits_count(long number) {
	int count = 0;

	while (number > 0) {
		number /= 10;
		count++;
	}

	return count;
}

int get_first_digits(long number, int count) {
    int treshold = pow(10, count);

    while (number > treshold) {
        number /= 10;
    }

    return number;
}

bool is_amex(long number) {
    int count = get_digits_count(number);
    int id = get_first_digits(number, 2);

    if (count != 15) {
        return false;
    }

    return id == 34 || id == 37;
}

bool is_mastercard(long number) {
    int count = get_digits_count(number);
    int id = get_first_digits(number, 2);

    if (count != 16) {
        return false;
    }

    return id == 51 || id == 52 || id == 53 || id == 54 || id == 55;
}

bool is_visa(long number) {
    int count = get_digits_count(number);
    int id = get_first_digits(number, 1);

    return id == 4 && (count == 13 || count == 16);
}
