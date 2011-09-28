#!/usr/bin/env python
from sys import argv
text = ''
if len(argv)< 2:
    text = raw_input("Please reinput the file name!\n>")
else:
    text = argv[1]
print ("Are you sure to truncate the file?")
raw_input("?")
print ("Open the file")
myfile = open(text, "w")

print ("Truncate the file!")
myfile.truncate()

print("write something new!")
firstline = raw_input("firstline:\n")
secondline = raw_input("secondline:\n")
thirdline = raw_input("thirdline:\n")

myfile.write(firstline)
myfile.write("\n")
myfile.write(secondline)
myfile.write("\n")
myfile.write(thirdline)
myfile.write("\n")
myfile.close()
