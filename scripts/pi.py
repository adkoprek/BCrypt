#  ____   _____ _______     _______ _______ 
# |  _ \ / ____|  __ \ \   / /  __ \__   __|
# | |_) | |    | |__) \ \_/ /| |__) | | |   
# |  _ <| |    |  _  / \   / |  ___/  | |   
# | |_) | |____| | \ \  | |  | |      | |   
# |____/ \_____|_|  \_\ |_|  |_|      |_|   
#   https://github.com/adkoprek/bcrypt
#
# Extract the digits of pi from pi.txt in assets
#
# This script prints the digits of pi in a format
# that can be easily copied into an c array
#
# @Author: Adam Koprek
# @Contributors: -
# @Licence: MIT

FILE = open('../assets/pi.txt', 'r')
READ_FILE = FILE.read()
SPLIT_FILE = READ_FILE.split("\n")
BLOCK_FILE = "".join(SPLIT_FILE)


def print_block(start: int, end: int):
    line = ''
    counter = 1

    print('{')
    for i in range(start + 1, end + 1):
        line += f"0x{BLOCK_FILE[((i - 1) * 8):((i - 1) * 8 + 8)]}, "
        if counter == 5:
            counter = 0
            print(f"    {line}")
            line = ""

        counter += 1

    print(f"    {line}")
    print('}')


if __name__ == '__main__':
    print_block(0, 18)
    print_block(18, 274)
    print_block(274, 530)
    print_block(530, 786)
    print_block(786, 1042)
