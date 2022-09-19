from random import randrange
# key - A 373 BC
# value - [0, 2**64 - 1]
OUTPUT_DATA_SIZE = 1000000
MAX_VALUE = 2 ** 64 - 1
MIN_VALUE = 0
result_data_file = open("data.txt", "w")
empty_string = '\n'
for i in range(OUTPUT_DATA_SIZE):
    first_letter = chr(randrange(65, 65 + 26))
    first_number = str(randrange(0, 10))
    second_number = str(randrange(0, 10))
    third_number = str(randrange(0, 10))
    second_letter = chr(randrange(65, 65 + 26))
    third_letter = chr(randrange(65, 65 + 26))
    result_string = first_letter + ' ' + first_number + second_number + third_number + ' ' + second_letter + third_letter
    result_string += '\t'
    result_string += str(randrange(MIN_VALUE, MAX_VALUE))
    result_string += '\n'
    result_data_file.write(result_string)
result_data_file.close()
