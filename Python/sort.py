# bubblesort
# [3,5,2,7,1,4,6]
# [3,2,5,1,4,6,7]
# [2,3,1,4,5,6,7]
# [2,1,3,4,5,6,7]
# [1,2,3,4,5,6,7]

# def ordenar_bubblesort(lista):
#     esta_ordenado= False
#     acumulador = 0
#     while esta_ordenado == False:
#         for posi in range(len(lista)- 1):
#             if lista[posi] > lista[posi + 1]:
#                 acumulador = lista[posi + 1]
#                 lista[posi + 1] = lista[posi]
#                 lista[posi] = acumulador

#         esta_ordenado = True
#         for posi in range(len(lista)- 1):
#             if lista[posi] > lista[posi + 1]:
#                 esta_ordenado=False
#     return lista

def bubblesort(lista):
    esta_ordenado = False
    acumulador = 0
    while esta_ordenado == False:
        esta_ordenado = True
        for posi in range(len(lista) - 1):
            if lista[posi] > lista[posi + 1]:
                acumulador = lista[posi + 1]
                lista[posi + 1] = lista[posi]
                lista[posi] = acumulador
                esta_ordenado = False
    return lista


lista = [3, 5, 2, 7, 1, 4, 6]
lista_ordenada = bubblesort(lista)
print(lista_ordenada)


# -----------------------------------------------------
# insertion sort
# [3,5,2,7,1,4,6]
# [3,5,2,7,1,4,6]
# [2,3,5,7,1,4,6]
# [2,3,5,7,1,4,6]
# [1,2,3,5,7,4,6]
# [1,2,3,4,5,7,6]
# [1,2,3,4,5,6,7]
def put_number_on_list(lista_ordenada: list, numero: int) -> list:
    lista_temp = []
    posi = 0
    numero_foi_inserido = False
    while posi < len(lista_ordenada):
        if numero_foi_inserido:
            lista_temp.append(lista_ordenada[posi])
        else:
            if lista_ordenada[posi] < numero:
                lista_temp.append(lista_ordenada[posi])
            else:
                lista_temp.append(numero)
                lista_temp.append(lista_ordenada[posi])
                numero_foi_inserido = True
        posi = posi+1
    if not numero_foi_inserido:
        lista_temp.append(numero)
    return lista_temp


def insertion_sort(lista):
    lista_ordenada = []
    for posi in range(len(lista)):
        numero = lista[posi]
        lista_ordenada = put_number_on_list(lista_ordenada, numero)
    return lista_ordenada


lista = [3, 5, 2, 7, 1, 4, 6]
lista_ordenada2 = insertion_sort(lista)
print(lista_ordenada2)


# -----------------------------------------------------
# selection sort

# 1)procurar o menor numero na parte desordenada
# 2)apaga-lo de sua posicao original
# 3)coloca-lo na ultima posicao do ordenados
# 4) volte para o passo 1 ate que a parte dos desordenados nao exista mais

def copy_list(lista: list) -> list:
    tamanho = len(lista)
    result = []
    for l in range(tamanho):
        result.append(lista[l])
    return result


def find_min_number(lista_ordenada, posi):
    menor = 9999999
    posi_menor = 0
    for posi1 in range(posi, len(lista_ordenada)):
        if lista_ordenada[posi1] < menor:
            menor = lista_ordenada[posi1]
            posi_menor = posi1
    return posi_menor


def put_number_on_list(posi: int, posi_menor: int, lista_ordenada: list):
    list_temp = copy_list(lista_ordenada)  # lista_ordenada[:]
    list_temp[posi] = lista_ordenada[posi_menor]
    list_temp[posi_menor] = lista_ordenada[posi]
    return list_temp


def selection_sort(lista):
    for posi in range(len(lista)):
        posi_menor = find_min_number(lista, posi)
        lista = put_number_on_list(posi, posi_menor, lista)
    return lista


lista = [3, 5, 2, 7, 1, 4, 6]
lista_ordenada3 = selection_sort(lista)
print(lista_ordenada3)

# -----------------------------------------------------
# merge-sort
# [3,5,2,7,1,4,6,9,10,8,11]
# [[3,5],[2,7],[1,4],[6,9],[10,8,11]]
# [[3,5],[2,7],[1,4],[6,9],[8,10,11]]
# aqui acaba a devisões
# [[2,3,5,7],[1,4,6,9],[8,10,11]]
# [[1,2,3,4,5,6,7,9],[8,10,11]]
# [[1,2,3,4,5,6,7,8,9,10,11]]

# dividir o conjunto maior em duplas ate precise ou nao do ultimo ser um trio
# organizar dentro dos mini conjuntos
# juntar  em duplas em um conjunto e organiza-las
# repetir passo 2 ate que todos os mini conjuntos estejam juntos e organizados


def split(lista: list) -> list[list]:  # [5, 3, 7, 2, 1, 4, 6]
    ls_temp = []
    dupla = []
    for posi in range(len(lista)):
        if (posi % 2 == 0):
            dupla.append(lista[posi])
        else:
            dupla.append(lista[posi])
            ls_temp.append(dupla[:])
            dupla = []
    if (len(dupla) == 1):
        ls_temp[-1].append(dupla[0])
    return ls_temp


def order(listas: list[list]):  # [[5, 3], [7, 2], [1, 4, 6]]
    for posi in range(len(listas)):
        if (listas[posi][0] > listas[posi][1]):
            conj_temp = []
            conj_temp.append(listas[posi][1])
            conj_temp.append(listas[posi][0])
            listas[posi] = conj_temp
            conj_temp = []


def merge(listas: list[list]) -> list:  # [[3, 5], [2, 7], [1, 4, 6]]
    while len(listas) > 1:
        primeira_lista = listas[0]  # [2,3,5,7]
        segunda_lista = listas[1]  # [1, 4, 6]
        lista_temp = []
        i = 0
        j = 0
        while i < len(primeira_lista) or j < len(segunda_lista):
            if i == len(primeira_lista) and j < len(segunda_lista):
                lista_temp.append(segunda_lista[j])
                j += 1
            elif j == len(segunda_lista) and i < len(primeira_lista):
                lista_temp.append(primeira_lista[i])
                i += 1
            else:
                if primeira_lista[i] < segunda_lista[j]:
                    lista_temp.append(primeira_lista[i])
                    i += 1
                else:
                    lista_temp.append(segunda_lista[j])
                    j += 1
        listas.pop(0)
        listas.pop(0)
        listas.insert(0, lista_temp)


def merge_sort(lista):
    lista_2_ou_3 = split(lista)
    order(lista_2_ou_3)
    merge(lista_2_ou_3)  # [1, 2, 3, 4, 5, 6, 7]
    return lista_2_ou_3[0]


lista = [5, 3, 7, 2, 1, 4, 6]
lista_ordenada3 = merge_sort(lista)
print(lista_ordenada3)
