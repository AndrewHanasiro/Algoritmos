# lista = [1,2,3,4,5]
# lista.append(6)
# print(lista) # [1,2,3,4,5,6]
# lista.append(999)
# print(lista) # [1,2,3,4,5,6,999]
# lista.pop()
# print(lista) # [1,2,3,4,5,6]

def media(lista):
    posicao = 0
    soma = 0
    quantidade = len(lista)
    while posicao < quantidade:
        soma = soma + lista[posicao]
        posicao = posicao + 1
        
    return soma/quantidade

l = []
entrada = 1
while entrada != 0: 
    entrada = int(input("insira um numero:"))
    l.append(entrada)
l.pop()
print(l)
result = media(l)
print (result)



# python .\media.py
# insira um numero: 50
# insira um numero: 75
# insira um numero: 10
# insira um numero: 25
# insira um numero: 0 <- indica o fim das entradas
# media = 40.0

