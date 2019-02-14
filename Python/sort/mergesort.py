sentinel = object()


def mergesort(vet: list):
    if len(vet) > 1:
        half = int(len(vet) / 2)
        left_half = vet[:half]
        right_half = vet[half:]
        mergesort(left_half)
        mergesort(right_half)
        merge(vet, left_half, right_half)


def merge(vet: list, left: list, right: list):
    i = 0
    j = 0
    k = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            vet[k] = left[i]
            i += 1
        else:
            vet[k] = right[j]
            j += 1
        k += 1
    while i < len(left):
        vet[k] = left[i]
        i += 1
        k += 1
    while j < len(right):
        vet[k] = right[j]
        j += 1
        k += 1
