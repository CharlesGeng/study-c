#Fibonacci数列函数
def fibo(x):
    if x < 2:
        return;
    result = [0, 1]
    for i in range(x - 2):
        result.append(result[-1] + result[-2])
    return result;

myarray = fibo(15)
print(myarray)

input("Press enter!")
