# A   1 or 11
# 2
# 3
# 4
# 5
# 6
# 7
# 8
# 9
# 10
# J   10
# Q   10
# K   10

import random

# retorna uma carta do baralho aleatoriamente
def give_card() -> int:
    return random.randrange(1,14)

# verifica se o usuário quer continuar a receber carta ou parar
def ask_continue() -> bool:
    y_or_n = input("deseja continuar?:")
    if y_or_n == "s":
        return True
    else:
        return False


# imprimir a lista de cartas
def print_cards(game_cards: list) -> None:
    print("as cartas sao :", end=" ")
    for Posi in range(len(game_cards)):
        if game_cards[Posi] == 1:
            print("A", end=" ")
        elif game_cards[Posi] == 11:
            print("J", end=" ")
        elif game_cards[Posi] == 12:
            print("Q", end=" ")
        elif game_cards[Posi] == 13:
            print("K", end=" ")
        else:
            print(game_cards[Posi], end=" ")
    print("\n")

    

# somar as cartas e retorna a soma. Vamos assumir que as casrtas estão ordenadas decrescente
def add_card(game_cards: list) -> int:
    soma = 0
    for Posi in range(len(game_cards)):
        if game_cards[Posi] == 1:
            if soma + 11 <= 21:
                soma = soma + 11
            else:
                soma = soma + 1
        elif game_cards[Posi] == 11 or game_cards[Posi] == 12 or game_cards[Posi] ==  13:
            soma = soma + 10
        else:   
            soma = soma + game_cards[Posi]
    return soma

#verificar se e menor que 21. Se for menor que 21 retorna False, se for maior ou igual retorna True
def verif_continue(soma: int) -> bool:
    if soma < 21:
        return False
    else:
        return True

def verif_continue_m(soma_m: int, soma_j_j: int) -> bool:
    if soma_m < 21 and soma_m < soma_j_j:
        return False
    else:
        return True

def verif_win_m(soma_m: int, soma_j_j: int) -> None: 
    if soma_m > soma_j_j:
        print("you won")
    else:
        print("a maquina perdeu")


#verificar se retorna you won ou gameover
def verif_win(soma: int) -> None:
    if soma == 21:
        print("You won")
    else:
        print("vez da maquina")    



def main ():
    game_cards_j = []
    game_cards_m = []
    fim = False
    soma_j = 0
    while not fim:
        carta = give_card()
        continuar = ask_continue()
        if continuar:
            game_cards_j.append(carta)
            print_cards(game_cards_j)
            game_cards_j.sort(reverse=True)
            soma_j=add_card(game_cards_j)
            print(soma_j)
            fim=verif_continue(soma_j)
        else:
            fim = True
    if soma_j < 21:
        fim = False
        while not fim:
            carta = give_card()
            game_cards_m.append(carta)
            print_cards(game_cards_m)
            game_cards_m.sort(reverse=True)
            soma_m=add_card(game_cards_m)
            print(soma_m)
            fim=verif_continue_m(soma_m, soma_j)            
        verif_win_m(soma_m,soma_j)
    else:
        print("gameover")
main()