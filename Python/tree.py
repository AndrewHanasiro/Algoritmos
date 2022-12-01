class Tree:
    def __init__(self) -> None:
        self.value = 0
        self.right = None
        self.left =  None
   
def recursiva(array:list) -> Tree:
    if len(array) == 0:
        return None
    posi = int(len(array)/2)
    arvore = Tree()
    arvore.value = array[posi]
    arvore.left = recursiva(array[0:posi])
    arvore.right = recursiva(array[posi+1:])
    return arvore

array_tree= [2,4,10,8,3]
root = recursiva(array_tree)
print(root.left.left.value)