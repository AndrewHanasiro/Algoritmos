import argparse
import random
import copy
import time
import sys
sys.setrecursionlimit(3000)

# Importing algorithms
from bubblesort import bubblesort
from quicksort import quicksort
from mergesort import mergesort


def generate(size: int) -> list:
    temp = []
    for _ in range(size):
        temp.append(random.randint(0, size))
    return temp


def sort(vet: list, key: str) -> list:
    algorithm = {
        "quicksort": quicksort,
        "bubblesort": bubblesort,
        "mergesort": mergesort
    }
    func = algorithm.get(key)
    if not func:
        print("Não existe o algoritmo %s implementado!" % key)
        return
    temp = copy.deepcopy(vet)
    func(temp)
    return temp


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='benchmark of sort algorithms')
    parser.add_argument(
        '-n', '--number', help='size of random list', type=int, required=True)
    parser.add_argument('-algs', '--algorithms',
                        nargs='+',
                        required=True,
                        help='list of algorithms sperate by comma')
    args = parser.parse_args()
    [algorithms, number] = args._get_kwargs()
    listA = generate(number[1])
    print("Original: %s" % listA)
    for alg in algorithms[1]:
        new_list = copy.deepcopy(listA)
        start = time.time()
        new_list = sort(new_list, alg)
        end = time.time()
        print(alg, new_list,end - start)

# python index.py -n 20 -algs quicksort, mergesort, bubblesort
