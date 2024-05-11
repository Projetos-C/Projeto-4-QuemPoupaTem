#include <stdio.h>
#include "functions.h"



int main(){

    func functions[] = { deposito, debito, transacao, extrato, novo_cliente, deletar_cliente, listar_cliente};
    Conta contas[TOTAL];
    int pos = 0;  
    int user;
    int auth = 0; // Autenticação
    int entrada; // Váriavel recebe a resposta do menu de entrada
    do{ 
        Value val;
        int entrada = menu_login(contas, &pos);

        // Caso o usuário queira fazer login:
        if(entrada == 1){
            val = login(contas, &pos, &user);
        }
        // Caso o usuário queira se cadastrar:
        else if(entrada == 2){
            val = cadastro(contas, &pos, &user);
            tratarRes(val);
        }
        // Caso o usuário queira sair;
        else if( entrada == 0){
            break;
        }

        if(val == OK){
            if(user > -2 && user < 1001){
                auth = 1;
            }
        }
    }while(auth == 0);

    int opcao;
    menu menus[] = {menu_adm, menu_user};
    do{
        if(user == -1){
            opcao = menus[0]();
        }
        else{
            opcao = menus[1]();
        }
         Value resposta = functions[opcao](contas, &pos, &user);

    }while(opcao != 0);
    
    
    
    return 0;
}
