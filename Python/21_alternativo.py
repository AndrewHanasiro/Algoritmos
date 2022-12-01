def main ():
    game_cards = []
    soma = 0
    fim = False
    continuar = True
    while not fim and continuar:
        carta = give_card()
        game_cards.append(carta)
        print_cards(game_cards)
        soma=add_card(game_cards)
        fim=verif_continue(soma)
        if not fim:
            continuar = ask_continue()
            if not continuar:
                print("gameover")
    verif_win(soma)