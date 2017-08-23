#importando as bibliotecas
from PIL import Image
import math
import os
import time
import sys

#setando variavel global para criação de log
global LOG
LOG=False

class Letra():
	def __init__(self,ind,letter):
		self.indice=ind
		self.letra=letter
		self.prox=[]

	def addLetter(self,palavra,count,word,ind):
		if len(word)==ind+1:
			new=Letra(count,word[ind])
			palavra.prox.append(new)
		else:
			if len(word)>ind+1:
				for i in range(len(palavra.getProx())):
					if palavra.prox[i].getLetra()==word[ind]:
						palavra.addLetter(palavra.prox[i],count,word,ind+1)

	def buscaIndex(self,palavra,word,ind):
		if len(word)==ind+1:
			return palavra.getIndice()
		else:
			for i in range(len(palavra.getProx())):
				if palavra.prox[i].getLetra()==word[ind+1]:
					return palavra.buscaIndex(palavra.prox[i],word,ind+1)
			return None #casos seja fim de árvore

	def buscaWord(self,palavra,ind):
		if ind==palavra.getIndice():
			resp=[]
			resp.append(palavra.getLetra())
			return resp
		else:
			for i in range(len(palavra.getProx())):
				temp=palavra.buscaWord(palavra.prox[i],ind)
				if temp!=None:
					new=[]
					new.append(palavra.getLetra())
					new+=temp
					return new
			return None

	def getIndice(self):
		return self.indice

	def getLetra(self):
		return self.letra

	def getProx(self):
		return self.prox

class Dicionario():
	def __init__(self, max_ind):
		self.max_ind=math.pow(2,max_ind)
		self.count=-1
		self.Palavras=[]
		for i in range(256):
			self.count+=1
			temp=Letra(self.count,i)
			self.Palavras.append(temp)

	def getCount(self):
		return self.count

	def getMax(self):
		return self.max_ind	

	def searchWord(self, ind):
		for i in range(len(self.Palavras)):
			temp = self.Palavras[i].buscaWord(self.Palavras[i],ind);
			if temp != None:
				return temp
		return None

	def searchIndex(self,word):
		return self.Palavras[word[0]].buscaIndex(self.Palavras[word[0]],word,0)

	def addPalavra(self,word):
		self.count+=1
		self.Palavras[word[0]].addLetter(self.Palavras[word[0]],self.count,word,1)

	def log(self):
		dic=open("encoder_dic.txt","w")
		print("Total de indice no dicionário: %d"%self.max_ind)
		print("Total de indice usados: %d"%self.count)
		for i in range(self.count):
			dic.write("%d-"%i)
			dic.write(str(self.searchWord(i)))
			dic.write("\n")
		dic.close()

class encoder():
	def __init__(self,maximo):
		self.entrada=[]
		self.saida=[]
		self.Height=0
		self.Width=0
		self.max_ind=maximo
		self.DIC=Dicionario(self.max_ind)

	def setEntrada(self,BMPfile):
		#pega o arquivo BMP
		self.entrada.clear()
		img = Image.open(BMPfile)
		self.Width,self.Height=img.size #W->Width e H-> Height
		for i in range(self.Height):
			for j in range(self.Width):
				(r,g,b)=img.getpixel((j,i))
				self.entrada.append(r)
				self.entrada.append(g)
				self.entrada.append(b)

	def encodeLZW(self):
		#algoritmo LZW
		ind=0
		ind2=0
		P=[]
		C=0
		new=[]
		while ind<len(self.entrada):
			ind=ind2
			os.system("cls")
			print("concluido={0:.2f} %".format(ind/len(self.entrada)*100))
			if(ind<len(self.entrada)):
				P.append(self.entrada[ind])
			else:
				break;
			while ind2<len(self.entrada):
				ind2+=1
				if ind2<len(self.entrada):
					C=self.entrada[ind2]
				else:
					C=-1
				new=P[:]
				new.append(C)
				idx=self.DIC.searchIndex(new)
				if idx != None: #achou no dicionario
					P.append(C)
				else:
					if C!=-1:
						if self.DIC.getCount() >= self.DIC.getMax():
							print("Dicionário está cheio")
							print("Total de indice no dicionário: %d"%self.DIC.getMax())
							print("Total de indice usados: %d"%self.DIC.getCount())
							exit(1)
						else:
							self.DIC.addPalavra(new)
					Pindex=self.DIC.searchIndex(P)
					self.saida.append(Pindex)
					P.clear()
					break;

	def writeBinary(self,BINfile):
		newFile = open(BINfile, "wb")		
		num_bits = self.DIC.getCount().bit_length()
		num_bytes=math.ceil(num_bits/8)
		newFile.write(self.Width.to_bytes(2,byteorder='big'))
		newFile.write(self.Width.to_bytes(2,byteorder='big'))
		newFile.write(self.max_ind.to_bytes(1,byteorder='big'))
		newFile.write(num_bits.to_bytes(1,byteorder='big'))
		memory=""
		print("Quantidade de bits necessário:%d"%num_bits)
		print("Tamanho da saída:%d"%len(self.saida))
		for i in range(len(self.saida)):
			N=bin(self.saida[i])[2:].zfill(num_bits)
			for idxN in range(len(N)):
				memory+=N[idxN]
				if len(memory)==num_bytes*8:
					result=int(memory,2)
					newFile.write(result.to_bytes(num_bytes,byteorder='big'))
					memory=""
		result=int(memory.zfill(num_bytes*8),2)
		newFile.write(result.to_bytes(num_bytes,byteorder='big'))
		newFile.close()

	def writeEntrada(self):
		entrada=open("encoder_input.txt","w")
		for i in range(len(self.entrada)):
			entrada.write("%d-"%self.entrada[i])
		entrada.close()

	def writeSaida(self):
		saida=open("encoder_output.txt","w")
		for i in range(len(self.saida)):
			saida.write("%d-"%self.saida[i])
		saida.close()

if __name__ == "__main__":
	for i in range(len(sys.argv)):
		if(sys.argv[i]=="-i"):
			entry = sys.argv[i+1]
		elif(sys.argv[i]=="-o"):
			out = sys.argv[i+1]
		elif(sys.argv[i]=="-n"):
			size = sys.argv[i+1]
	ENC=encoder(size)
	ENC.setEntrada(entry)
	start_time = time.time()
	ENC.encodeLZW()
	print("--- %s seconds ---" % (time.time() - start_time))
	ENC.writeBinary(out)
	if LOG==True:
		ENC.writeEntrada()
		ENC.writeSaida()
		ENC.DIC.log()