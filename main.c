#include <stdio.h>
#include "functions.h"



int main(){

    func functions[] = {novo_cliente, deletar_cliente, listar_cliente, debito, deposito, extrato, transacao};
    Conta contas[TOTAL];
    int pos = 0;

    int opcao;   
    int user = 0;

    do{
        menu_login(contas, &pos);
    }while(opcao != 0 || user != 0);

}
