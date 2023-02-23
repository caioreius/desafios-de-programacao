def tres(n):
    if n == 1: 
        return 1
    return 1 + tres (3 * n + 1 if n % 2 else n // 2)

def getMaxCycle(i, j):
    cycles = []
    for k in range(i, j + 1):
        cycles.append(tres(k))
    return max(cycles)


while (True):
    try:
        i, j = str(input()).split()
        print(i, j, getMaxCycle(int(i), int(j)))
    except EOFError: 
        break
