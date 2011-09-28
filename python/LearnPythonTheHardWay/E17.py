#! /usr/bin/env python
from sys import argv
from os.path import exists

scriptname, fromFile, toFile = argv
inputFile = open(fromFile, "r")
outputFile = open(toFile, "w")

print ("Read source file.")
inputdata= inputFile.read()

print ("Write to destination file.")
outputFile.write(inputdata)

inputFile.close()
outputFile.close()
print("copy finished!")
