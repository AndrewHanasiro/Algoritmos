sentinel = object()


def quicksort(vet: list, init=0, end=sentinel):
    if end == sentinel:
        end = len(vet) - 1
    pivo = int((init + end)/2)
    i = init
    j = end
    while i <= j:
        while(vet[i] < vet[pivo] and i < end):
            i += 1
        while(vet[pivo] < vet[j] and j > init):
            j -= 1
        if i <= j:
            aux = vet[i]
            vet[i] = vet[j]
            vet[j] = aux
            i += 1
            j -= 1
    if init < j:
        quicksort(vet, init, j+1)
    if i < end:
        quicksort(vet, i, end)
