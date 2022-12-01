def fatorial(n):
    if(n==1):
        return 1
    return n * fatorial(n-1)


result = fatorial(7)
print(result)

# fatorial(7) => 7 * fatorial(6)
# fatorial(7) => 7 * 6 * fatorial(5)
# .
# .
# fatorial(7) => 7 * 6 * 5 * 4 * 3 * 2 * fatorial(1)
# fatorial(7) => 7 * 6 * 5 * 4 * 3 * 2 * 1

# ---------------------------------------------------------------
def fibbonaci(n):
    if(n > 2):
        return fibbonaci(n-2) + fibbonaci(n-1)
    else:
        return 1
    
# 1 1 2 3 5 8 13 21
result2 = fibbonaci(5)
print(result2)

# fibbonaci(5) => fibbonaci(3) + fibbonaci(4)
# fibbonaci(5) => fibbonaci(1) + fibbonaci(2)) + fibbonaci(2) + fibbonaci(3)
# fibbonaci(5) => 1 + 1 + 1 + fibbonaci(1) + fibbonaci(2)
# fibbonaci(5) => 1 + 1 + 1 + 1 + 1