# read file line by line
# for each line
# cat it to /dev/ttyUSB0
# wait for response

import sys
import os
import time
from datetime import datetime #test

filename = sys.argv[1]
ttyfilename = sys.argv[2]

# Using readlines()
file1 = open(filename, 'r')
Lines = file1.readlines()

count = 0
# Strips the newline character

with open(ttyfilename, 'r') as the_file:
    with open(ttyfilename, 'w') as writetty:

        print("Erasing sector 1:")
        writetty.write("erase sector 1\n")
        response = the_file.readline()

        if response[0] == 'O':
            print("Done..")
        else:
            print("FAIL ERASE 1\n")
            sys.exit(1)

        print("Erasing sector 2:")
        writetty.write("erase sector 2\n")
        response = the_file.readline()

        if response[0] == 'O':
            print("Done..")
        else:
            print("FAIL ERASE 2\n")
            sys.exit(1)

        for line in Lines:
            count += 1
            print("Line{}: {}".format(count, line.strip()))

            #print(line.encode('utf-8').hex())

            writetty.write(line)

            t1 = datetime.now()
            response = the_file.readline()
            t2 = datetime.now()
            delta = t2 - t1
            print("delta micros : " , (delta.microseconds))
            print("len resp : " , len(response))
            if response[0] != 'O':
                print("BAD")
                print("RESPONSE IS: " , response)
                sys.exit(1)
            
            print("wrote")
