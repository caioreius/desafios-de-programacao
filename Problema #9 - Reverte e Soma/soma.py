def reverse(num):
    return int(str(num)[::-1])

number = int(input())

while (True):
    try:
        number = int(input())
        numberReversed = reverse(number)

        count = 0
        while (True):
            if (number == numberReversed):
                print(count, number)
                break
            else:
                number += numberReversed
                numberReversed = reverse(number)
                #print(number)
            count += 1
    except EOFError:
        break;
