def main():
    height = get_height()

    for floor in range(1, height + 1):
        draw(floor, height)


def get_height():
    while True:
        try:
            height = int(input('Height: '))
        except ValueError:
            pass
        else:
            if height > 0 and height < 9:
                return height



def draw(floor, height):
    offset = ' ' * (height - floor)
    sharps = '#' * floor
    line = f'{offset}{sharps}  {sharps}'
    print(line)


if __name__ == '__main__':
    main()
