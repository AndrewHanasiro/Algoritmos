#importando bibliotecas
import random
import string
import threading

#Probabilidade de dar cross-over
global GLOBAL_PC
GLOBAL_PC = 0.7

#Probabilidade de dar mutação
global GLOBAL_PM
GLOBAL_PM = 0.01

#Tamanho da populaçao
global GLOBAL_POPSIZE
GLOBAL_POPSIZE = 200

#Quantidade de geração a ser desenvolvidas
global GLOBAL_GENEN
GLOBAL_GENEN = 200

class Individual:
	def __init__(self,DNAsize):
		self.dna=[]
		self.fitness=0
		for i in range(DNAsize):
			self.dna.append(random.choice(string.ascii_letters))

	def mutation(self,goal):
		luck=random.random()
		if luck<GLOBAL_PM:
			idx=random.randrange(len(goal))
			letter=random.choice(string.ascii_letters)
			self.dna[idx]=letter

	def calculateFitness(self,goal):
		for letter in range(len(goal)):
			if goal[letter]==self.dna[letter]:
				self.fitness+=1

	def getFitness(self):
		return self.fitness

class Population:
	def __init__(self):
		self.population=[]
		self.newPopulation=[]
		self.goal=str(input("qual a frase obejtivo:"))
		for i in range(GLOBAL_POPSIZE):
			self.population.append(Individual(len(self.goal)))

	def PartnerSelection(self,soma):
		idx=-1
		while True:
			idx=random.randrange(GLOBAL_POPSIZE)
			reject_accept=random.randrange(soma)
			if reject_accept<self.population[idx].getFitness():
				return self.population[idx]

	def CrossOver(self,indA,indB):
		luck=random.random()
		if luck<GLOBAL_PC:
			Filho=Individual(len(self.goal))
			idx=random.randrange(len(self.goal))
			for i in range(len(self.goal)):
				if i < idx:
					Filho.dna[i]=indA.dna[i]
				else:
					Filho.dna[i]=indB.dna[i]
			Filho.mutation(self.goal)
			return Filho
		else:
			return None

	def NaturalSelection(self):
		soma=0
		for i in range(GLOBAL_POPSIZE):
			self.population[i].calculateFitness(self.goal)
			soma+=self.population[i].getFitness()
		A=self.PartnerSelection(soma)
		B=self.PartnerSelection(soma)
		Filho=self.CrossOver(A,B)
		if Filho!=None :
			self.newPopulation.append(Filho)

	def stopcriteria(self,gen):
		best=0
		idxbest=-1
		AvFit=0
		for i in range(GLOBAL_POPSIZE):
			self.population[i].calculateFitness(self.goal)
			AvFit+=self.population[i].getFitness()
			if self.population[i].getFitness() > best :
				best=self.population[i].getFitness()
				idxbest=i
		AvFit/=GLOBAL_POPSIZE
		phrase=''.join(self.population[idxbest].dna)
		print("Generation:%d\tAverage Fitness:%f\tBest Attempt:%s"%(gen,AvFit,phrase))
		if best==len(self.goal):
			return 1	
		return 0

	def live(self):
		stop=0
		for gen in range(GLOBAL_GENEN):
			self.newPopulation.clear()
			while len(self.newPopulation)<GLOBAL_POPSIZE:
				self.NaturalSelection()
			for i in range(GLOBAL_POPSIZE):
				self.population[i]=self.newPopulation[i]			
			stop=self.stopcriteria(gen)
			if stop == 1:				
				break;

if __name__ == "__main__":
	P=Population()
	#print("Probabilidade de cross-over:%d\%"%(int(GLOBAL_PC*100)))
	#print("Probabilidade de mutacao:%d\%"%(int(GLOBAL_PM*100)))
	P.live()
		
