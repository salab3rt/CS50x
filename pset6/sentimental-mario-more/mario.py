# TODO


def main():

    max_height = 8
    height = 0
    spac = 0

    # Keep prompting user for height, if conditions aren't met
    while height < 1 or height > max_height:
        # Use try, to catch letters, floats etc
        try:
            # Get user height input
            height = int(input('Choose pyramid height? '))

        except:
            print('Invalid pyramid height')

    print_pyramid(height, spac)


def print_pyramid(height, spac):
    # base case
    if height > 0:

        # Use recursion to print pyramid lines, where height - 1 dictates number of blocks to print,
        # and spac the number of spaces before the blocks
        print_pyramid(height - 1, spac + 1)

        # Print Blocks
        print(' ' * spac, '#' * height, '  ', '#' * height, sep='')


if __name__ == '__main__':
    main()