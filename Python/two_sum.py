# Input: 2
# Input: 7
# Input: 11
# Input: 15
# Input: -1
# target: 13
# Output: [0,2]
# Output: Because nums[0] + nums[2] == 13, we return [1, 2].

# X + Y

# x   Y   2   7   11  15    
# 2       -   9   13  17
# 7       9   -   18  22
# 11      13  18  -   26 
# 15      17  22  26  -

def two(lista, objetivo):
    t = 0
    for x1 in range(len(lista)):
        for y2 in range(len(lista)): 
            
            if (lista[x1] + lista[y2] == objetivo and x1 != y2):
                return (x1,y2)

n = int(input("coloque o resultado:"))

l = []
entrada = 1

while entrada != -1: 
    entrada = int(input("insira um numero:"))
    l.append(entrada)
l.pop()
print(l)
result = two(l,n)
print (result)



