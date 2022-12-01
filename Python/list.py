# lista = [1,2,1,5,8,6,9,4,3,5,7,4,0,4]
# lista_number = [8,4,1]
# resultado = [1,3,2]

def func_count(x, y):
    list_count = []
    print(len(x), len(y))
    for posi in range(len(y)):
        count = 0
        for posi2 in range(len(x)):
            if y[posi] == x[posi2]:
                count = count + 1
        list_count.append(count)
    print(list_count)


lista = [1, 2, 1, 5, 8, 6, 9, 4, 3, 5, 7, 4, 0, 4]
lista_number = [8, 4, 1]
func_count(lista, lista_number)
