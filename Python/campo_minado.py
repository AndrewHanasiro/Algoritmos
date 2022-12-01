{# 1 - bomba
# 0 - seguro
# 1   0   0
# 0   0   0
# 0   1   0
# campo_resposta = [[1,0,0], [0,0,0], [0,1,0]]

# -1 - bomba
# N - numero de bombas ao redor
# -1    1       0
# 2     2       1
# 1     -1      1
# campo_numero = [[-1,1,0], [2,2,1], [1,-1,1]]

# L C   0   1   2   3   4
# 0     1   0   0   0   1
# 1     1   0   1   0   0
# 2     0   0   0   0   1
# 3     0   1   0   1   0
# 4     1   0   0   0   1
# campo_resposta = [[1,0,0,0,1],[1,0,1,0,0],[0,0,0,0,1][0,1,0,0,0][1,0,0,0,1]]

# campo_numero = gera_campo_numeros(campo_resposta)
def incrementa_todos_adjacente(linha,coluna,campo):
    limit_colun = len(campo[0])-1
    limit_linh = len(campo) - 1
    novo_campo = copy_board(campo)
    for l in [-1,0,1]:
        for c in [-1,0,1]:
            if (l == -1 or c == -1) and (linha+l < 0 or coluna+c < 0):
                continue
            if (l == 1 or c == 1) and (linha+l > limit_linh or coluna+c > limit_colun):
                continue
            if novo_campo[linha+l][coluna+c] == -1:
                continue                
            novo_campo[linha+l][coluna+c] += 1
    return novo_campo

def copy_board(campo):
    linhas=len(campo)
    colunas=len(campo[0])
    result = []
    for l in range(linhas):
        linha = []
        for c in range(colunas):
            linha.append(campo[l][c])
        result.append(linha)
    return result

def gera_campo_numeros(campo):
    campo_bomba = generate_campo(len(campo),len(campo[0]))
    for linha in range(len(campo)):
        for coluna in range(len(campo[linha])):
            if campo[linha][coluna] != 0: #verificação se for bomba
                campo_bomba[linha][coluna] = -1

    for linha in range(len(campo)):
        for coluna in range(len(campo[linha])):
            if campo[linha][coluna] != 0:
                campo_bomba=incrementa_todos_adjacente(linha,coluna,campo_bomba)
    return campo_bomba


def generate_campo(linhas, colunas):
    result = []
    for l in range(linhas):
        linha = []
        for c in range(colunas):
            linha.append(0)
        result.append(linha)
    return result

def imprimir_campo(campo_numero, campo_input):
    for linha in range(len(campo_numero)):
        for coluna in range(len(campo_numero[linha])):
            if(campo_input[linha][coluna] == 1):
                print("%d\t"%campo_numero[linha][coluna], end =" ")
            else:
                print("*\t", end =" ")
        print("\n")
    print("-----------------------------------")

def start(colun, linh, campo_resposta, campo_input, campo_numero):
    while campo_resposta[linh][colun] == 0:
        campo_input[linh][colun] = 1
        imprimir_campo(campo_numero, campo_input)
        if verifica_win(campo_resposta,campo_input):
            return("won")
        colun= int(input("coloque a coluna: "))
        linh = int(input("coloque a linha: "))
    else:
        return("game over")   

def verifica_win(campo_resposta,campo_input):
    for verif1 in range(len(campo_resposta)):
        for verif2 in range(len(campo_resposta[verif1])):
            if campo_resposta[verif1][verif2] == campo_input[verif1][verif2]:
                return False
    return True

def main ():
    campo_resposta = [[1,0,0,0,1],[1,0,1,0,0],[0,0,0,0,1],[0,1,0,0,0],[1,0,0,0,1]]
    campo_numero = gera_campo_numeros(campo_resposta)
    campo_input = [[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]
    imprimir_campo(campo_numero, campo_input)
    input_p1 = int(input("coloque a coluna: "))
    input_p2 = int(input("coloque a linha: "))
    result = start(input_p1,input_p2,campo_resposta,campo_input,campo_numero)
    print (result)

main()
# 1 imprimir campo totalmente coberto
# 2 pegar a entrada de usuario
# 3 verificar se a entrada de usuario e bomba
#     - se sim retornar gameover
#     - se nao
#         1 imprimir o campo com numero correspondente a entrada do usuario
#         2 verificar se o todos os campos exceto o -1 foram abertos
#             -  se naovolte para o passo 2
#             - se sim escrever you won
