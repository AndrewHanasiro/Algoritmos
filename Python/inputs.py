def potencia(base, exp):
    i = 0
    acc = 1
    while i < exp:
        acc = acc * base
        i += 1
    return acc

input_base = int(input("coloque a base:"))
input_exp = int(input("coloque o expoente:"))
result = potencia(input_base, input_exp)
print(result)
