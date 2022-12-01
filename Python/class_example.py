

# andar frente, virar esquerda, virar a direita, ré*
# combustivel, reabastecer
# grana
# abrir porta mala*
# empinar*
class Vehicle:
    fuel = 0
    def turn_left(self):
        pass

    def go_forward(self):
        pass

    def turn_right(self):
        pass
    def __init__(self,max_fuel):
        self.max_fuel = max_fuel
        
    def pfuel(self,quant):
        
        if quant + self.fuel<= self.max_fuel:
            self.fuel= quant + self.fuel
            return(self.fuel)
        else:
            self.fuel = self.max_fuel
            return(self.max_fuel)
   

class VehicleWithGoBack:
    def go_back(self):
        pass

class VehicleWithTrunk:
    def open_trunk(self):
        print("trunk open")

class Car(Vehicle, VehicleWithGoBack,VehicleWithTrunk):
    num_wheels = 4
   

    def wheels(self):
        return self.num_wheels

    def payTax(self, variacao: float):
        return variacao * self.num_wheels
    def __init__(self):
        super().__init__(45)
class Moto(Vehicle):
   
    def __init__(self, num_wheels):
        if num_wheels > 3:
            msg = "não existe moto com {} rodas".format(num_wheels)
            raise Exception(msg)
        self.num_wheels = num_wheels
        super().__init__(9)

    def empinar(self):
        if self.num_wheels > 2:
            raise Exception("não da pra empinar com 3 ou mais rodas")
        else:
            print("empianndo")
    

class Bus(Vehicle):
    def __init__(self):
        super().__init__(500)
    def wheels(self):
        return ("8")


class Truck(Vehicle):
    def __init__(self):
        super().__init__(450)
    def wheels(self):
        return ("6")
   
v1 = Car()
v1.turn_left()
v1.go_forward()
v1.go_back()

v1.open_trunk()
print(v1.pfuel(40))

v2 = Moto(2)
v2.empinar()
print(v2.pfuel(40))

v3 = Bus()
print(v3.pfuel(40))

v4 = Truck()

print(v4.pfuel(100))
print(v4.pfuel(200))