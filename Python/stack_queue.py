# Stack: FILO

def append(num,lista):
    return lista + [num]
    
def build_list(lista:list, index:int):
    lista_n = []
    for posi in range(len(lista)):
        if index != posi:
            lista_n = append(lista[posi], lista_n)
    return lista_n

def pop(lista, index = -1):
    num_f = lista[index]
    lista_f = build_list(lista, index)
    return (num_f, lista_f)

queue=[]
queue=append("p1", queue)
queue=append("p2", queue)
queue=append("p3", queue)
queue=append("p4", queue)
(p4,queue)=pop(queue)
(p3,queue)=pop(queue)
(p2,queue)=pop(queue)
(p1,queue)=pop(queue)
print(p1,p2,p3,p4)

# Queue: FIFO
queue=[]
queue=append("p1", queue)
queue=append("p2", queue)
queue=append("p3", queue)
queue=append("p4", queue)
(p1,queue)=pop(queue,0)
(p2,queue)=pop(queue,0)
(p3,queue)=pop(queue,0)
(p4,queue)=pop(queue,0)
print(p1,p2,p3,p4)

