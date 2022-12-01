# Numero palíndromo: 

# 123321
# 1758571

# numero: 121
# sim

# numero: 123
# nao

# numero: 3
# sim

def palindromo(x):
    tam = None
    if (len(x) % 2 == 0):
        tam = int(len(x) / 2)
    else:
        tam = int((len(x) - 1) / 2)
    for pos in range(tam - 1):
        if(x[pos] != x[len(x) - 1 - pos]):
            return False
    return True

x=input("qlq coisa:")
print(palindromo(x))