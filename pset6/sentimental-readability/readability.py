# TODO
import re


def main():

    try:
        text = input('Text: ')
        cli = cl_index(text)
    except Exception as e:
        print(e)

    if cli > 16:
        print('Grade 16+')
    elif cli < 1:
        print('Before Grade 1')
    else:
        print('Grade', cli)

    exit()


def cl_index(text):

    if not len(text.split()):
        exit(1)

    letters = len(re.findall('\w', text))   # Letter counter
    words = len(text.split())       # Word counter
    sentences = len(re.findall('\.|\!|\?', text))   # Count sentences by counting the number of ". ! ?"

    l = float(float(letters / words) * 100)     # Average letters per 100 words
    s = float(float(sentences / words) * 100)   # Average sentences per 100 words
    cli = 0.0588 * l - 0.296 * s - 15.8     # Coleman-Liau index formula

    return round(cli)   # Return rounded index to the nearest integer


if __name__ == '__main__':
    main()
