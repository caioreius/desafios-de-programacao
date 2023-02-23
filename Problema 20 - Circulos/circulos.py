import math

def distancia_luizinho(k, l, reg):
    return math.sqrt(math.pow(reg[k] + reg[l], 2) - math.pow(abs(reg[k] - reg[l]), 2))

def calc_width_box(circulos):
    max_width = 0
    dp = [0] * 8

    dp[0] = circulos[0]

    for i in range(1, len(circulos)):
        for j in range(0, i):
            max_width = max(max_width, dp[j] + distancia_luizinho(i, j, circulos))
        dp[i] = max(circulos[i], max_width)

    for i in range(0, len(circulos)):
        max_width = max(max_width, dp[i] + circulos[i])

    return max_width

def process_soluction(circulos):
    return 2 * circulos[0] if len(circulos) == 1 else calc_width_box(circulos)

def permuta(v, start, end):
    if start == end - 1:
        return process_soluction(v)
    else:
        min_width = 0
        for i in range(start, end):
            tmp = v[i]
            v[i] = v[start]
            v[start] = tmp

            w = permuta(v, start + 1, end)
            if w < min_width or min_width == 0:
                min_width = w

            v[start] = v[i]
            v[i] = tmp

        return min_width

n_cases = int(input())

if n_cases > 50:
    exit()

for i in range(n_cases):
    radiis = [float(x) for x in input().split()[1:]]
    print("%.3f" % permuta(radiis, 0, len(radiis)))
