def primo(x):
    
    f = 2    
    while f < x/2:
        if x % f == 0:
            return "nao e primo"
        else:
            f = f + 1
    return "e primo"


input_n = int(input("coloque um numero:"))
result = primo(input_n)
print(result)

# Definição: só é dividido por 1 e por ele mesmo, portanto nenhum dos numeros menores que ele vai dividir

# numero: 89
# 2
# 3
# 4
# 5
# 6
# 7
# 8
# 9
# 10
# 11
# 12
# 13
# 14
# 15
# 16
# .
# .
# .
# 88