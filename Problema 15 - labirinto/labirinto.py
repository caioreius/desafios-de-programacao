# Equipe lambda

longest = 0

def solve_lab(i, j): 
    global longest
    direction = [[-1,0],[1,0],[0,-1],[0,1]]
    Q = []
    Q.append([i,j])
    length = 1
    is_cycle = 1
    cur = None
    nxt = None
    while len(Q) > 0:
        length += 1
        cur = Q.pop(0)

        for x in range(4):
            nxt = [cur[0] + direction[x][0], cur[1] + direction[x][1]]
            if nxt[0] < 0 or nxt[1] < 0 or nxt[0] >= H or nxt[1] >= W:
                is_cycle = 0
                continue
            if lab[nxt[0]][nxt[1]] == 0:
                lab[nxt[0]][nxt[1]] = 1
                Q.append(nxt)

    if is_cycle == 0: return 0
    length /= 3
    if longest < length: longest = int (length)
    return 1

def read_lab(H, W):
    lab = [[0] * W * 3 for _ in range(H * 3)]

    for i in range(H):
        line = input()
        for j in range(W):
            ii = i * 3
            jj = j * 3
            for x in range(3):
                for y in range(3):
                    lab[ii+x][jj+y] = 0
            if line[j] == '\\':
                lab[ii][jj] = 1
                lab[ii+1][jj+1] = 1
                lab[ii+2][jj+2] = 1
            else:
                lab[ii][jj+2] = 1
                lab[ii+1][jj+1] = 1
                lab[ii+2][jj] = 1
    return lab

# Resolve o labirinto
Case = 1
while True:

    # Processar cada caso
    W, H = map(int, input().split())

    if W == 0 and H == 0: break

    lab = read_lab(H, W)

    H *= 3
    W *= 3

    num_cycles = 0
    longest = 0
    for i in range(H):
        for j in range(W):
            if lab[i][j] == 0:
                if solve_lab(i, j):
                    num_cycles += 1

    # Printar
    print(f"Maze #{Case}:")
    if num_cycles:
        print(f"{num_cycles} Cycles; the longest has length {longest}.")
    else:
        print("There are no cycles.")
    print()
    
    Case += 1
