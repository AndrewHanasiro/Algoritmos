# filter
# função que recebe uma lista e função de condição que filtra
# [1,2,3,4,5,6]
# n%2==0
# [2,4,6]

def filter_function(lista, func_filter):
    result = []
    for posi in range(len(lista)):
        number = lista[posi]
        if func_filter(number):
            result.append(number)
    return result

def func_filter(number) -> bool:
    return number%2 == 0

def main():
    lista= [1,2,3,4,5,6]
    retorno = filter_function(lista, func_filter)
    print(retorno)

main()

# mapeamento
# função que recebe uma lista e executa a função de alteração
# [1,2,3,4,5,6]
# n*2
# [2,4,6,8,10,12]

def map_function(lista2, func_map):
    result2 = []
    for posi in range(len(lista2)):
        number = lista2[posi]
        r_numero = func_map(number)
        result2.append(r_numero)
    print(result2)

def func_map(numero)->int:
    return numero*2
    
def main2():
    lista2 = [1,2,3,4,5,6]
    map_function(lista2, func_map)
main2()



