#!/usr/bin/env python

def func(x, y, z):
    return x+y+z
print func(21,22,13)


f = lambda x, y, z: x+y+z
print f(12,11,2)


x = (lambda a="fee", b="fie", c="Foe": a+b+c)
print x("Test", "Taste")

def Test(title = "sir"):
    act = (lambda name: title + " " + name)
    return act
action = Test()
print action("Gunn")

L = [(lambda x : x ** 2),(lambda x : x ** 3),(lambda x : x ** 4)]
print L[0](2)
for l in L:
    print l(2),
print ""

dic = { "A": lambda : 1,
        "B": lambda : 2,
        "C": lambda : 3,
        }
for key in sorted(dic.keys()):
    print dic[key]()

lower = (lambda x, y : x if x < y else y)
print "which is lower, 12 or 13 ? " + str(lower(12, 13))
print "which is lower, 13 or 12 ? " + str(lower(13, 12))

def action(x):
    return (lambda y : x ** y)

act = action(2)
print act(4)
