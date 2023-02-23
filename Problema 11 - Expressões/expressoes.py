# vetor para armazenar os valores já calculados do problema catalan (programação dinâmica)
catalanNumbers = [0 for i in range(200)]
# matriz para armazenar os valores já calculados do problema expr (programação dinâmica)
calculated_values_for_l_d = []

def initDp(n, d):
    global calculated_values_for_l_d
    for i in range(n + 100):
        calculated_values_for_l_d.append([0 for j in range(d + 100)])


def catalan(n):
    global catalanNumbers
    if catalanNumbers[n] != 0:
        return catalanNumbers[n]

    a = b = j = 1
    for i in range(n + 1, 2 * n + 1):
        a *= i
        b *= j
        j += 1

    b = b * (n + 1)
    a = a // b
    catalanNumbers[n] = a
    return a

def calc(l, d):
    #print(l, d)
    global calculated_values_for_l_d
    if calculated_values_for_l_d[l][d] != 0:
        return calculated_values_for_l_d[l][d]

    if d * 2 > l:
        return 0

    if d * 2 == l or d == 1:
        return 1

    a = calc(l - 2, d)

    for i in range(2, l - 1, 2):
        n = 0
        j = d + 1
        while calc(l - i - 2, j) != 0:
            n += calc(l - i - 2, j)
            j += 1

        c1 = catalan((l - i - 2) // 2) - n

        c = calc(i, d - 1) * c1
        n = 0

        j = d
        while calc(i, j) != 0:
            n += calc(i, j)
            j += 1

        c2 = catalan(i // 2) - n
        e = c2 - calc(i, d - 1)
        f = calc(l - i - 2, d) * e
        a += f + c

    calculated_values_for_l_d[l][d] = a
    return a


if __name__ == "__main__":
    while True:
        try:
            n, d = map(int, input().split())
            initDp(n, d)
            print(calc(n, d))
        except (EOFError, ValueError, KeyboardInterrupt):
            break
