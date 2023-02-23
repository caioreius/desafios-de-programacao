def fibonacciInterval(limitInf, limitSup):
    # check if the number of terms is valid
    n1, n2 = 1, 1
    count = 0
    while n2 <= limitSup:
        #print(n1)
        nth = n1 + n2
        # update values
        n1 = n2
        n2 = nth
        if n1 >= limitInf: count += 1
    return count

while (True):
    try:
        limitInf, limitSup = [int(i) for i in input().split()]
        if (limitInf == limitSup == 0):
            break
        count = fibonacciInterval(limitInf, limitSup)
        print(count)
    except EOFError:
        break
