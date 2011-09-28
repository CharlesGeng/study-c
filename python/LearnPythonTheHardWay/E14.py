from sys import argv
user = argv[1]
prompt = "<"
print "Hi %s, I'm the %s script." % (user, argv[0])
print "Do you like me %s?" % user
isLike = raw_input(prompt)
print "Where do you live %s?" % user
address = raw_input(prompt)
print "What kind of computer do you have?"
computer = raw_input(prompt)

print """
Alright, so you said '%s' about liking me.
You live in '%s'.  Not sure where that is.
And you have a '%s' computer.  Nice.
""" % (isLike, address, computer)
