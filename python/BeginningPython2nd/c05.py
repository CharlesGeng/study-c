#num = input("Please enter a number:")
#num = int(num)
#if num > 0:
#	print ('You input a positive number!')
#elif num < 0:
#	print ('You input a negative number!')
#else:
#    print ('You input a zero!')
#key = input("Please select type, color(c) or number(n):")
#if key == 'c':
#    color = input ("Please select a color, Red(r), Green(g), Blue(b):")
#    if color == 'r':
#        print('You selected red')
#    elif color == 'g':
#        print('You selected green')
#    elif color == 'b':
#        print('You selected blue')
#    else:
#        print("Illegal color type!")
#else:
#    print ("You select number!")
#测试while
#name = ''
#while not name.strip():
#    name = input("Please input your name:")
#print("Hello, %s!" % name)
x={'a':'1', 'b':'2', 'c':'3'}
for key in x.keys():
    print (key, x[key])
input("Press enter to exit.")
