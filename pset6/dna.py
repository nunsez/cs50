import sys
import csv
import re


def main():
    if len(sys.argv) != 3:
        print('Usage: python dna.py database sequence')
        sys.exit(1)

    db = load_database(sys.argv[1])
    seq = load_sequence(sys.argv[2])

    str_list = list(db[0].keys())[1:]
    longest_substrs = dict.fromkeys(str_list, 0)

    for i in str_list:
        substring = get_longest_substr(i, seq)
        longest_substrs[i] = substring.count(i)

    person = find_matched_person(db, longest_substrs.copy())

    print(person)


def load_database(path):
    with open(path) as csvfile:
        db = []
        db_reader = csv.DictReader(csvfile)

        for row in db_reader:
            entry = {}

            for k, v in row.items():
                entry[k] = v if k == 'name' else int(v)

            db.append(entry)

        return db


def load_sequence(path):
    with open(path) as txtfile:
        seq = txtfile.read()

        return seq


def get_longest_substr(substring, string):
    pattern = rf'({substring})+'
    result = re.finditer(pattern, string)

    try:
        longest_substr = max([i[0] for i in result])
    except ValueError:
        longest_substr = ''

    return longest_substr


def find_matched_person(db, seq_data):
    for person in db:
        person_name = person['name']
        seq_data['name'] = person_name

        if person == seq_data:
            return(person_name)

    return('No match')


if __name__ == '__main__':
    main()
