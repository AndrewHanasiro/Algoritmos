class Animal:
	_peso=None;
	_altura=None;
	def __init__(self, P, A):
		self._peso=P;
		self._altura=A;

	def noise(self):
		pass

	def medidas(self):
		print ('Peso:' + self._peso + '\nAltura:' + self._altura);

class Cat(Animal):

	def noise(self):
		print ('Miau');

class Dog(Animal):

	def noise(self):
		print ('Auf'); 

