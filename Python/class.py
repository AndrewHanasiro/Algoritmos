#teste


class Operacao:
	A=None;
	B=None;
	def __init__ (self,A,B):
		self.A=A;
		self.B=B;

	def imprimir(self):
		print ('A=' + str(self.A) + '\tB=' + str(self.B));

	def Soma(self):
		return (self.A+self.B);

	def Subtracao(self):
		return (self.A-self.B);

	def Produto(self):
		return (self.A*self.B);


print ("Testando classes:");
K=Operacao(10,3.5);
K.imprimir();
print('soma=' + str(K.Soma()));
print('subtracao=' + str(K.Subtracao()));
print('produto=' + str(K.Produto()));
