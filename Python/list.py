import random
class Father:
	def __init__(self,name,age):
		self.name=name
		self.age=age
		self.filhos=[]

	def addFilhos(self,entrada):
		print("entrada:")
		print(entrada)
		for i in entrada:
			print("i: %d, filho:%d"%(i,entrada[i]))
			self.filhos.append(entrada[i])

fathers=[]

for i in range(4):
	fathers.append(Father("A",i))
	k=range(i+1)
	print("ANTES :%d"%len(fathers[i].filhos))
	fathers[i].addFilhos(k)
	print("DEPOIS :%d"%len(fathers[i].filhos))

for i in range(4):
	for j in range(len(fathers[i].filhos)):
		print("Pai: %d, Filho: %d, lenfilhos: %d"%(i,j,len(fathers[i].filhos)))

lista=[]
for i in range(10):
	lista.append(i)
print(lista)
for i in reversed(lista):
	print(lista[i])
for i in range(10):
	print("escolhido:%d"%random.choice(lista))
print("soma=%d"%sum(lista))

lst1=[1,2,3,4,5,6]
lst2=[1,1,1,1,1,1]
print(lst1+lst2) #nao funciona
lst3=[]
for i in range(len(lst1)):
	lst3.append(lst1[i]+lst2[i])
print(lst3)
for i in range(5):
	print(random.randrange(5))

