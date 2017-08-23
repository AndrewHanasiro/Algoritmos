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
			ltr=[]
			ltr.append(palavra.getLetra())
			return ltr
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
		#print("adicionando palavra:%s"%word)
		self.Palavras[word[0]].addLetter(self.Palavras[word[0]],self.count,word,1)

	def log(self):
		dic=open("decoder_dic.txt","w")
		print("Total de indice no dicionário: %d"%self.max_ind)
		print("Total de indice usados: %d"%self.count)
		for i in range(self.count):
			dic.write("%d-"%i)
			dic.write(str(self.searchWord(i)))
			dic.write("\n")
		dic.close()

class decoder():
	def __init__(self):
		self.entrada=[]
		self.saida=[]
		self.Height=0
		self.Width=0
		self.DIC=None

	def setEntrada(self,BINfile):
		self.entrada.clear()
		#pega o arquivo Binário
		newFile = open(BINfile, "rb")
		self.Width=int.from_bytes(newFile.read(2), byteorder='big')
		self.Height=int.from_bytes(newFile.read(2), byteorder='big')
		max_ind=int.from_bytes(newFile.read(1), byteorder='big')
		num_bits=int.from_bytes(newFile.read(1), byteorder='big')
		num_bytes=math.ceil(num_bits/8)
		print("numero de bits:%d\nnumero de bytes sendo lido:%d"%(num_bits,num_bytes))
		self.DIC=Dicionario(max_ind)
		result=""
		memory=int.from_bytes(newFile.read(num_bytes), byteorder='big')
		while True:
			reserva=int.from_bytes(newFile.read(num_bytes), byteorder='big')
			temp=bin(memory)[2:].zfill(num_bytes*8)
			if reserva==0:
				#tratar o temp
				i=0
				while temp[i]=='0':
					i+=1
				new=temp[i:]
				for idx in range(len(new)):
					result+=new[idx]
					if len(result)==num_bits:
						self.entrada.append(int(result,2))
						result=""
				break
			else:
				for idx in range(len(temp)):
					result+=temp[idx]
					if len(result)==num_bits:
						self.entrada.append(int(result,2))
						result=""
				memory=reserva

	def decodeLZW(self):
		C=[]
		P=[]
		P=self.DIC.searchWord(self.entrada[0])
		fp=open("teste.txt","w")
		for i in range(len(self.entrada)):
			self.saida+=P
			fp.write("%d - %s\n"%(self.entrada[i],P))
			if i+1<len(self.entrada):
				C=self.DIC.searchWord(self.entrada[i+1])
				if C!=None:
					P.append(C[0])
				else:
					P.append(P[0])
			if self.DIC.getCount()<self.DIC.getMax():
				self.DIC.addPalavra(P)
				if C!=None:
					P=C[:]
				else:
					P=self.DIC.searchWord(self.entrada[i+1])
			else:
				print("Dicionario já esta cheio\n")
		fp.close()

	def writeBMP(self,BMPfile):
		img = Image.new("RGB",(self.Width,self.Height))
		print(img.size)
		k=0
		for i in range(self.Height):
			for j in range(self.Width):
				img.putpixel((j,i),(self.saida[k],self.saida[k+1],self.saida[k+2]))
				k+=3
		img.save(BMPfile,"BMP")
		img.close()

	def writeEntrada(self):
		entrada=open("decoder_input.txt","w")
		for i in range(len(self.entrada)):
			entrada.write("%d-"%self.entrada[i])
		entrada.close()

	def writeSaida(self):
		saida=open("decoder_output.txt","w")
		for i in range(len(self.saida)):
			saida.write("%d-"%self.saida[i])
		saida.close()

if __name__ == "__main__":	
	ENC=decoder()
	ENC.setEntrada("05.bin")
	start_time = time.time()
	ENC.decodeLZW()
	print("--- %s seconds ---" % (time.time() - start_time))
	ENC.writeBMP("final05.bmp")
	if LOG==True:
		ENC.writeEntrada()
		ENC.writeSaida()
		#ENC.DIC.log()
	