# defina uma função chamada calculadora vai receber 3 argumentos

# calculadora(123,456,"+") => 123 + 456
# calculadora(123,456,"-") => 123 - 456
# calculadora(456,123,"-") => 456 - 123 
# calculadora(123,456,"/") => 123 / 456
# calculadora(123,456,"*") => 123 * 456


def calculadora(x,y,operador):
    if(operador == "+"):
        return soma(x,y)
    elif(operador == "-"):
        return subt(x,y)
    elif(operador == "*"):
        return mult(x,y) 
    elif(operador == "/"): 
        return div(x,y)
    else:
        print("operador inválido")


def soma(x,y):
    resultado = x + y
    return resultado

def subt(x,y):
    result = x - y
    return result

def mult(x,y):
    result2 = x * y
    return result2

def div(x,y):
    result3 = x / y
    return result3

resultado_final=calculadora(11,8,"*")
print(resultado_final)
