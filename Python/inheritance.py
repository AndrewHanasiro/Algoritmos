class Animal:
    def __init__(self, P, A):
        self._peso = P
        self._altura = A

    def noise(self):
        print("Grrr")

    def medidas(self):
        print("Peso:%d \nAltura:%d" % (self._peso, self._altura))


class Cat(Animal):
    def __init__(self, P, A):
        Animal.__init__(self, P, A)

    def noise(self):
        print('Miau')


class Dog(Animal):
    def __init__(self, P, A):
        Animal.__init__(self, P*2, A*2)

    def noise(self):
        print('Auf')


C = Cat(25, 50)
C.noise()
C.medidas()
D = Dog(25, 50)
D.noise()
D.medidas()
