sentinel = object()


def bubblesort(vet: list, ind=0, end=True):
    if ind == len(vet)-1:
        if end == True:
            return
        else:
            bubblesort(vet, 0, True)
    else:
        if(vet[ind] > vet[ind+1]):
            aux = vet[ind]
            vet[ind] = vet[ind+1]
            vet[ind+1] = aux
            bubblesort(vet, ind+1, False)
        bubblesort(vet, ind+1, end)
