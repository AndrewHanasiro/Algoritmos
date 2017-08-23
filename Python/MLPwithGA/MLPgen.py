#	Problema:
#
#	Ajustar o pesos através do algoritmo genético de um MLP
#	contendo 3 camada: a de entrada com 2500 input,
#	a escondida com 200 neurônios e a de saída com 10 neuronios

#importando bibliotecas
import random
import numpy as np
from PIL import Image 

# ---------------------------------- Rede Neural Globals ----------------------------------

#Setando uma variável gloabal que refere-se ao tamanho da imagem
global GLOBAL_TAM
GLOBAL_TAM=50

#Setando uma variável global que refere-se quantidade de saída/classe
global GLOBAL_OUTPUT
GLOBAL_OUTPUT=10

#Setando uma variável global que refere-se quantidade diferente de padrão
global GLOBAL_QUANTPATTERN
GLOBAL_QUANTPATTERN=100

#Setando uma variável global que refere-se quantidade diferente de versões
global GLOBAL_QUANTVERSION
GLOBAL_QUANTVERSION=10

#Setando uma variável global que refere-se quantidade camadas
global GLOBAL_QUANTLAYERS
GLOBAL_QUANTLAYERS=3

#Quantidade de neurônios na camada escondida
global GLOBAL_HIDDENNEURON
GLOBAL_HIDDENNEURON=20

#Setando uma variável global que refere-se ao valor máximo do pixel
global GLOBAL_MAXPIXELVALUE
GLOBAL_MAXPIXELVALUE=255

#Setando uma variável global que refere-se ao valor da ativação quando é estimuladora
global GLOBAL_ATIVESTIM
GLOBAL_ATIVESTIM=1

#Setando uma variável global que refere-se ao valor da ativação quando é inibidora
global GLOBAL_ATIVINIB
GLOBAL_ATIVINIB=-1

# ---------------------------------- Algoritmo Genético Globals----------------------------------

#Probabilidade de dar cross-over
global GLOBAL_PC
GLOBAL_PC = 0.7

#Probabilidade de dar mutação
global GLOBAL_PM
GLOBAL_PM = 0.01

#Porcentagem da populatção que será mantida (elitismo)
global GLOBAL_ELITE
GLOBAL_ELITE = 0.3

#Tamanho da populaçao
global GLOBAL_POPSIZE
GLOBAL_POPSIZE = 20

#Quantidade de geração a ser desenvolvidas
global GLOBAL_GENEN
GLOBAL_GENEN = 200

#Tamanho do DNA que é a quantidade de pesos a serem ajustados
global GLOBAL_DNASIZE 
GLOBAL_DNASIZE=(GLOBAL_TAM*GLOBAL_TAM+1)*GLOBAL_HIDDENNEURON+(GLOBAL_HIDDENNEURON+1)*GLOBAL_OUTPUT

def sigmoide(x,deriv=False): #Função Sigmoide
	if(deriv==True): #verificando se é a derivada da função de ativação
		if(x<-40 or x>40):
			return 0
		else:
			return 1/(np.cosh(x)+1)
	else: #função de ativação normal
		if(x<-40): #Se x for menor do que 40, retorna -1
			return GLOBAL_ATIVINIB
		else:
			if(x>40): #Se x for maior do que 40, retorna 1
				return GLOBAL_ATIVESTIM
			else: #Se x estiver entre -40 e 40 faça a conta
				return np.tanh(x/2) #garante que a raiz seja 0 e a saida varie entre -1 < x < 1

class BaseTraining: 
	def __init__(self): #Construtor dos Dados de treinamento
		self.base=[] #cria uma lista que representa os diferentes padrões
		self.quant=GLOBAL_QUANTPATTERN

	def reset(self): #reseta a lista 
		self.base.clear() #zerando a lista de figuras
		for i in range(self.quant):
			self.base.append(i)

	def choose(self): #Vendo entre os padrão qual vai ser escolhido
		while True:
			idx=random.randrange(self.quant) #escolhendo um indice aleatorio
			if(self.base[idx]!=-1): #que não tenha sido escolhido antes
				num=self.base[idx]
				self.base[idx]=-1
				break
		return num

	def shuffle(self): #embaralhando a lista
		for i in range(int(self.quant/2)):
			luck=random.random()
			idx=random.randrange(self.quant/2-1)
			if(luck>=0.5):
				k=self.base[idx]
				self.base[idx]=self.base[int(idx+self.quant/2)]
				self.base[int(idx+self.quant/2)]=k
			else:
				k=self.base[idx]
				self.base[idx]=self.base[self.quant-1-idx]
				self.base[self.quant-1-idx]=k

class Neuron:
	def __init__(self,NumEntry): #Construtor de um neuronio com pesos randomicos entre 0<=w<=1 e pede-se o valor do bias para o usuario
		self.weight=[]
		self.NumEntry=NumEntry
		
	def soma(self,entrada): #Soma linearmente as entradas vezes o peso
		result=0
		for i in range(self.NumEntry):
			result+=entrada[i]*self.weight[i]
		result+=self.bias
		return result

	def getNeuronOutput(self,entrada): #output do neuronio sendo -1 ou 1
		total_lin = self.soma(entrada) #Pega o Valor da Somatória
		sinal = sigmoide(total_lin) #Passa pela função sigmoide
		return sinal

	def getWeight(self): #retorna a lsita de peso associada ao neuronio
		return self.weight

	def neuronWeightUpdate(self,newWeight,newBias):
		self.weight.clear()
		for i in range(self.NumEntry):
			self.weight.append(newWeight[i])
		self.bias=newBias


class EntryLayer:
	def __init__(self,NumEntry): #Contrutor da camdada de entrada onde não há neuronio
		self.entry=[]
		self.NumEntry=NumEntry
		
	def setLayerEntry(self, entrada): #Coloca as entradas da camada de entrada
		for i in range(self.NumEntry):
			self.entry.append(entrada[i])

	def getLayerOutput(self): #Retorna a saida uma lista que representa a saida da camada de entrada, neste caso, a saída é igual a entrada
		return self.entry

	def getNumOutput(self): #Retorna a quantidade de entrada
		return self.NumEntry

class HiddenLayer:
	def __init__(self,NumEntry): #Construtor da camadas escondidas, há neuronio neste caso
		self.neurons=[] 
		self.output=[]
		self.entry=[]
		self.NumEntry=NumEntry #O numero de entrada é igual a quantidade de neuronio da camada anterior
		self.NumNeuron = GLOBAL_HIDDENNEURON
		for i in range(self.NumNeuron):
			temp=Neuron(self.NumEntry)
			self.neurons.append(temp)

	def getLayerOutput(self): #Retorna uma lista que contêm os output de cada neuronio contido nesta camada
		self.output.clear()
		for i in range(self.NumNeuron):
			self.output.append(self.neurons[i].getNeuronOutput(self.entry))
		return self.output

	def getNumNeuron(self): #Retorna o numero de neuronios
		return self.NumNeuron

	def getNumOutput(self): #Retorna o numero de output que a camdada tem
		return self.NumNeuron

	def setLayerEntry(self, entrada): #Coloca as entradas em cada neuronio
		self.entry.clear()
		for i in range(self.NumEntry):
			self.entry.append(entrada[i])

class OutLayer:
	def __init__(self,NumEntry): #Contrutor da camdada de saída, ou seja última camada onde há neuronio
		self.output=[]
		self.neurons=[]
		self.entry=[]
		self.NumEntry=NumEntry
		self.NumNeuron=GLOBAL_OUTPUT #há apenas GLOBAL_OUTPUT neuronios nesta camada, isto está setado na variáveis globais
		for i in range(self.NumNeuron):
			temp=Neuron(self.NumEntry)
			self.neurons.append(temp)

	def getLayerOutput(self): #Retorna uma lista que contêm os output de cada neuronio contido nesta camada
		self.output.clear()
		for i in range(self.NumNeuron):
			self.output.append(self.neurons[i].getNeuronOutput(self.entry))
		return self.output

	def getNumNeuron(self): #Retorna o numero de neuronios
		return self.NumNeuron

	def getNumOutput(self): #Retorna o numero de output que a camdada tem
		return self.NumNeuron

	def getGrad(self): #retorna uma lista de grad que representa o grad para cada neuronio
		return self.grad

	def setLayerEntry(self, entrada): #Coloca as entradas em cada neuronio
		self.entry.clear()
		for i in range(self.NumEntry):
			self.entry.append(entrada[i])

class Network:
	def __init__(self): #inicia um modelo de ANN não recorrente
		self.layers=[] #Lista de que contém as camadas
		self.finalOutput=[] #Saida real
		self.answer=[] #Saída Desejada
		self.classe=0 #Classe do digito pode ser entre 0-9
		self.versao=0 #Versão do digito
		self.PatternError=[] #Erro calculado após cada ciclo sendo que será erro=(1/2)*(D-Y)**2
		self.num_Layer = GLOBAL_QUANTLAYERS
		for i in range(self.num_Layer):
			if(i==0): #Coloca a camada de entrada
				print("Fazendo a camada de entrada")
				self.layers.append(EntryLayer(GLOBAL_TAM*GLOBAL_TAM))
			else:
				if(i==self.num_Layer-1): #Coloca a camada de saída
					print("Fazendo a camada de saida")
					self.layers.append(OutLayer(self.layers[i-1].getNumOutput()))
				else: #Coloca a camada escondida
					print("Fazendo a camada escondida")
					self.layers.append(HiddenLayer(self.layers[i-1].getNumOutput()))
		#setando o gabarito
		self.answer=[
			[GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM,GLOBAL_ATIVINIB],
			[GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVINIB,GLOBAL_ATIVESTIM]]
	
	def updateWeights(self,DNA):
		i=0
		for L in range(1,self.num_Layer):
			for N in range(self.layers[L].getNumNeuron()):
				NumEntry=self.layers[L].NumEntry
				self.layers[L].neurons[N].neuronWeightUpdate(DNA[i:i+NumEntry],DNA[i+NumEntry])
				i+=NumEntry+1


	def newInput(self,num): #Coloca um novo input de treinamento
		self.versao=int(num%10)
		self.classe=int((num-num%10)/10)
		entrada=[] #lista que conterá os valores de cada pixel da imagem
		entrada.clear()
		file_name="pattern/c%dv%d.jpg" % (self.classe,self.versao)
		img = Image.open(file_name).convert("L")
		W,H=img.size #W->Width e H-> Height
		for i in range(H):
			for j in range(W):
				entrada.append(img.getpixel((i,j))/GLOBAL_MAXPIXELVALUE)
		self.layers[0].setLayerEntry(entrada) #Coloca os valores do pixel na camada de entrada
		img.close() #fecha o ponteiro referente ao arquivo
	
	def feedforward(self):
		entrada=[]
		error=[]
		SumError=0
		self.finalOutput.clear() #reseta a saida pra cada feedforward
		for i in range(1,self.num_Layer): #Como na camada de entrada não há neuronio, então vamos começar a partir da primeira camada escondida
			entrada=self.layers[i-1].getLayerOutput() #A saida de uma camada
			self.layers[i].setLayerEntry(entrada)  #É a entrada da proxima
			entrada.clear()
		self.finalOutput=self.layers[self.num_Layer-1].getLayerOutput() #pegando a Saida Real
		for i in range(GLOBAL_OUTPUT): #calcular o erro
			error.append(self.answer[self.classe][i]-self.finalOutput[i]) #calcula o erro=d-y | d é desejda e y é a real
			SumError+=(error[i]**2)/2 #faz com que o erro seja a diferença elevado ao quadrado divido por 2
		self.PatternError.append(SumError)

	def learn(self,DNA,BT): #treina a ANN
		BT.reset()
		self.PatternError.clear() #reseta o erro do padrao
		self.updateWeights(DNA)
		for pattern in range(GLOBAL_QUANTPATTERN): #Garantindo que apresenta todos os padrões
			BT.shuffle() #Embaralha a base para
			self.newInput(BT.choose()) #Escolhe um padrão aleatório como entrada
			self.feedforward()
		return self.PatternError

class Individual:
	def __init__(self):
		self.dna=[]
		self.fitness=0
		self.error=[]
		for i in range(GLOBAL_DNASIZE):
			self.dna.append(random.gauss(0,1))

	def mutation(self):
		luck=random.random()
		if luck<GLOBAL_PM:
			idx=random.randrange(GLOBAL_DNASIZE)
			weight=random.gauss(0,1)
			self.dna[idx]=weight

	def calculateFitness(self,MLP,BT):
		self.error=MLP.learn(self.dna,BT)
		soma=0
		for pattern in range(GLOBAL_QUANTPATTERN):
			soma+=self.error[pattern]
		self.fitness=soma/GLOBAL_QUANTPATTERN
		print("Soma dos Errors:%f \tfitness:%f"%(soma,self.fitness))

	def getFitness(self):
		return self.fitness

	def getDna(self):
		return self.dna

	def setDna(self, newdna, newfitness):
		self.dna.clear()
		for i in range(len(newdna)):
			self.dna.append(newdna[i])
		self.fitness=newfitness

class Population:
	def __init__(self):
		self.population=[]
		self.newPopulation=[]
		self.goal=float(input("Qual a erro médio máximo:"))
		for i in range(GLOBAL_POPSIZE):
			print("Criando individuo %d.."%i)
			self.population.append(Individual())
		print("População criada")

	def stopcriteria(self,gen,MLP,BT):
		best=np.inf
		idxbest=-1
		AvFit=0
		for i in range(GLOBAL_POPSIZE):
			self.population[i].calculateFitness(MLP,BT)
			AvFit+=self.population[i].getFitness()
			if self.population[i].getFitness() < best :
				best=self.population[i].getFitness()
				idxbest=i
		AvFit/=GLOBAL_POPSIZE
		print("Generation:%d\tAverage:%f\tBest:%f"%(gen,AvFit,self.population[idxbest].getFitness()))
		if best<=self.goal:
			return 1
		return 0

	def bubblesort(self):
		while True:
			cond=0
			for i in range(GLOBAL_POPSIZE-1):
				if self.population[i].getFitness()>self.population[i+1].getFitness():
					temp=Individual()
					temp.setDna(self.population[i].getDna(),self.population[i].getFitness())
					self.population[i].setDna(self.population[i+1].getDna(),self.population[i+1].getFitness())
					self.population[i+1].setDna(temp.getDna(),temp.getFitness())
					cond=1
			if cond==0:
				break

	def elitism(self):
		self.bubblesort()
		ind=0
		while len(self.newPopulation)<int(GLOBAL_POPSIZE*GLOBAL_ELITE):
			self.newPopulation.append(self.population[ind])
			ind+=1

	def PartnerSelection(self,soma):
		idx=None
		while True:
			idx=random.randrange(GLOBAL_POPSIZE)
			reject_accept=random.uniform(0,soma)
			if self.population[idx].getFitness()<reject_accept:
				return self.population[idx]

	def CrossOver(self,indA,indB):
		luck=random.random()
		if luck<GLOBAL_PC:
			Filho=Individual()
			#verificando qual dos pais tem amior fitness
			if indA.getFitness()>indB.getFitness():
				idx=(indA.getFitness()/(indA.getFitness()+indB.getFitness()))*100/GLOBAL_DNASIZE
			else:
				idx=(indB.getFitness()/(indA.getFitness()+indB.getFitness()))*100/GLOBAL_DNASIZE
			for i in range(GLOBAL_DNASIZE):
				if i < idx:
					Filho.dna[i]=indA.dna[i]
				else:
					Filho.dna[i]=indB.dna[i]
			Filho.mutation()
			return Filho
		else:
			return None

	def NaturalSelection(self):
		soma=0
		for i in range(GLOBAL_POPSIZE):
			soma+=self.population[i].getFitness()
		A=self.PartnerSelection(soma)
		B=self.PartnerSelection(soma)
		Filho=self.CrossOver(A,B)
		if Filho!=None :
			self.newPopulation.append(Filho)

	def live(self):
		stop=0
		MLP=Network()
		BT=BaseTraining() #Cria uma base de treinamento
		for gen in range(GLOBAL_GENEN):
			self.newPopulation.clear()
			stop=self.stopcriteria(gen,MLP,BT)
			if stop == 1:
				break;
			self.elitism()
			while len(self.newPopulation)<GLOBAL_POPSIZE:
				self.NaturalSelection()

			for i in range(GLOBAL_POPSIZE):
				self.population[i]=self.newPopulation[i]			

if __name__ == "__main__":
	P=Population()
	P.live()
		
