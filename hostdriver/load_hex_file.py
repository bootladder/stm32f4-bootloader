# read file line by line
# for each line
# cat it to /dev/ttyUSB0
# wait for response

import sys
import os
import time

filename = sys.argv[1]
ttyfilename = sys.argv[2]

# Using readlines()
file1 = open(filename, 'r')
Lines = file1.readlines()

count = 0
# Strips the newline character

with open(ttyfilename, 'r') as the_file:...
    with open(ttyfilename, 'w') as writetty:
9
        for line in Lines:
            count += 1
            print("Line{}: {}".format(count, line.strip()))

            writetty.write(line)

            response = the_file.readline()

            if response[0] != 'Y':
                print("BAD")
                sys.exit(1)
