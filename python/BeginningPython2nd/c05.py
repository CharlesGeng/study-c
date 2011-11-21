#num = input("Please enter a number:")
#num = int(num)
#if num > 0:
#	print ('You input a positive number!')
#elif num < 0:
#	print ('You input a negative number!')
#else:
#    print ('You input a zero!')


key = input("Please select type, color(c) or number(n):")
if key == 'c':
    color = input ("Please select a color, Red(r), Green(g), Blue(b):")
    if color == 'r':
        print('You selected red')
    elif color == 'g':
        print('You selected green')
    elif color == 'b':
        print('You selected blue')
    else:
        print("Illegal color type!")
else:
    print ("You select number!")
