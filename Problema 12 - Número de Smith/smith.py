import math
import sys

sqrt_int = lambda x: int(math.sqrt(x))

def fatores_primos(n):
    fatores = []
    c = n
    while ((c % 2 == 0)):
    
        fatores.append(2)
        c = c / 2
    
    i = 3
    while (i <= math.sqrt(c) + 1):
    
        if (c % i == 0):
        
            fatores.append(i)
            c = c / i
        
        else:
            i = i + 2
    
    if (c > 1):
        fatores.append(c)
    
    return fatores
 
def sum(arr):
    soma = 0
    for i in arr:
        soma+=i
    return soma
        
# Soma algorismos de um número
sum_alg = lambda x: sum([int(i) for i in str(x)])

# Dado o vetor arr = [2, 12, 23, 3], sum_arr(arr) é o mesmo que 2 + (1 + 2) + (2 + 3) + 3, o que nos dá o retorno igual à 13
sum_arr = lambda arr: sum([sum_alg(int(number)) for number in arr])

# 
def smith(number): 
    i = number + 1
    while True:
        alg_sum = sum_alg(i)
        factors = fatores_primos(i)
        if len(factors) == 1: 
            i += 1
            continue
        
        sum_alg_factors = sum_arr(factors)
        if alg_sum == sum_alg_factors: return i
        
        i += 1

def init():
    input()
    while True:
        try: 
            number = int(input())
            print(smith(number))
        except EOFError:
            break
        
init()
