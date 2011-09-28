from sys import argv
script, fileName = argv
print ("The script name : %r" % script)
text = open(fileName)
print ("The file--%r content is :" % fileName)
print (text.read())
