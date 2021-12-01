import cs50


def main():
    height = get_height()

    for floor in range(1, height + 1):
        draw(floor, height)


def get_height():
    while True:
        height = cs50.get_int('Height: ')

        if height > 0 and height < 9:
            return height


def draw(floor, height):
    offset = ' ' * (height - floor)
    sharps = '#' * floor
    line = f'{offset}{sharps}  {sharps}'
    print(line)


if __name__ == '__main__':
    main()
