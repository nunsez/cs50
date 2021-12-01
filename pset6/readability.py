import cs50
import re


def main():
    text = cs50.get_string('Text: ')
    index = get_readability_index(text)
    print_grade(index)


def get_readability_index(text):
    letters = len(re.findall(r'[a-zA-Z]', text))
    words = len(re.findall(r'\S+', text))
    sentences = len(re.findall(r'[.?!]', text))

    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    return index


def print_grade(index):
    grade = round(index)

    if grade >= 16:
        print('Grade 16+')
    elif grade < 1:
        print('Before Grade 1')
    else:
        print(f'Grade {grade}')


if __name__ == '__main__':
    main()
