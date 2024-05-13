#include <stdio.h>
#include "functions.h"



int main(){

    func functions[] = { deposito, debito, transacao, extrato, novo_cliente, listar_cliente, deletar_cliente}; 
    arc arquivo[] = {salvar, carregar};
    Conta contas[TOTAL];
    int pos = 0;  
    int user;
    int auth = 0; // Autenticação
    int entrada; // Váriavel recebe a resposta do menu de entrada
    Value carregar = arquivo[1](contas, &pos);


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
            opcao = menus[1]();
        }
        else{
            opcao = menus[0]();
        }
        opcao--;
        printf("%d\n %d\n", pos, opcao);
        Value resposta = functions[opcao](contas, &pos, &user);

    }while(opcao != -1);
    Value salvar = arquivo[0](contas, &pos);
    
    
    
    return 0;
}
