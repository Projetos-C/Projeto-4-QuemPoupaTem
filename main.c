#include <stdio.h>
#include "functions.h"



int main(){

    func functions[] = { deposito, debito, transacao, extrato, novo_cliente, listar_cliente, deletar_cliente}; // Lista de funções principais
    menu menus[] = {menu_login, menu_adm, menu_user}; // Lista de funções do tipo menu
    arc arquivo[] = {salvar, carregar}; // Lista de funções de maniplação de arquivo

    // Variaveis Iniciais
    Conta contas[TOTAL]; 
    int pos = 0;  
    int user;
    int auth = 0; // Autenticação
    int entrada; // Váriavel recebe a resposta do menu de entrada

    Value carregar = arquivo[1](contas, &pos);
    tratarRes(carregar);

    do{ 
        Value val;
        int entrada = menus[0](); // Login

        // Caso o usuário queira fazer login:
        if(entrada == 1){
            val = login(contas, &pos, &user);
        }
        // Caso o usuário queira se cadastrar:
        else if(entrada == 2){
            user = -2;
            val = functions[4](contas, &pos, &user); // Cadastro, -2 Se refere a cadastro de um novo cliente por ele mesmo
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
    do{
        if(user == -1){
            opcao = menus[1](); // Adm
            opcao--;
            if(opcao == -1){
                printf("| > Encerrando...\n");
            }
            else if(opcao >= 0 && opcao <= 6){
                Value funcao =functions[opcao](contas, &pos, &user);
                tratarRes(funcao);
            }
            else{
                printf("| > Opção Inválida...\n");
            }
        }
        else{
            opcao = menus[2](); // User
            opcao--;
            if(opcao == -1){
                printf("| > Encerrando...\n");
            }
            else if(opcao >= 0 && opcao <= 3){
                Value funcao = functions[opcao](contas, &pos, &user);
                tratarRes(funcao);
            }
            else{
                printf("| > Opção Inválida...\n");
            }
        }


    }while(opcao != -1);
    Value salvar = arquivo[0](contas, &pos);
    tratarRes(salvar);

    return 0;
}
