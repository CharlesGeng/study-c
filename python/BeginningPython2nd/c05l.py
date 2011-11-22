#! /usr/bin/env python3
x = {'a':'1', 'b':'2', 'c':'3'}
for key in x.keys():
    print (key, x[key])

for val in x.values():
    print(val)


import math
for x in range(99, 0, -1):
    root = math.sqrt(x)
    if root == int(root):
        print ('Max number is:', x)
        break

x = list(range(1,100,2))
for val in x:
    if val%2 == 0:
        print (x)
        break;
else:
    print("Did not break!")

#得到10以内数字的平方的列表
import math
mylist = [math.pow(x, 2) for x in list(range(0,10))]
print (mylist)

#得到10以内偶数的平方的列表
mylist = [math.pow(x, 2) for x in list(range(0,10)) if x % 2 == 0]
print (mylist)

