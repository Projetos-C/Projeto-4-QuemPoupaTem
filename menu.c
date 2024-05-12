#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"





int menu_login(){
    int opcao;
    
    do{
        printf("\n\033[34m");
        printf("|==================================|\n");
        printf("|- - -| Banco Quem Poupa Tem |- - -|\n");
        printf("|==================================|\n");
        printf("| > Menu de Login:                 |\n");
        printf("|   1 - Fazer Login                |\n");
        printf("|   2 - Fazer Cadastro             |\n");
        printf("|   0 - Sair                       |\n");
        printf("|==================================|\n");
        printf("| > Escolha uma opcao: ");
        scanf("%d", &opcao);
        clearBuffer();
        
        if(opcao <= 2 && opcao >= 1){
            return opcao;
        }
        else if(opcao == 0){
            break;
        }
        else{
            printf("\033[31m| > Opcao Invalida, Tente novamente...\n");
        }
    }while(opcao != 0);
    return 0;
}

int menu_adm(){
    int opcao;
    int validation = 0;
    
    do{
        printf("\n\033[34m");
        printf("|==================================|\n");
        printf("|- - -| Banco Quem Poupa Tem |- - -|\n");
        printf("|==================================|\n");
        printf("| > Menu de Administrador:         |\n");
        printf("|   1 - Deposito                   |\n");
        printf("|   2 - Debito                     |\n");
        printf("|   3 - Transferencia              |\n");
        printf("|   4 - Extrato                    |\n");
        printf("|   5 - Criar Usuário              |\n");
        printf("|   6 - Listar Usuários            |\n");
        printf("|   7 - Deletar Usuário            |\n");
        printf("|   0 - Sair                       |\n");
        printf("|==================================|\n");
        printf("| > Escolha uma opcao: ");
        scanf("%d", &opcao);
        clearBuffer();

        if(opcao <= 7 && opcao >= 0){
            validation = 1;
        }
        else{
            printf("\033[31m| | > Opcao Invalida, tente novamente.\n");
        }
    }while(validation = 0);
    
    return opcao;
}

int menu_user(){
    int opcao;
    int validation = 0;
    
    do{
        printf("\n\033[34m");
        printf("|==================================|\n");
        printf("|- - -| Banco Quem Poupa Tem |- - -|\n");
        printf("|==================================|\n");
        printf("| > Menu de Usuario:               |\n");
        printf("|   1 - Deposito                   |\n");
        printf("|   2 - Debito                     |\n");
        printf("|   3 - Transferencia              |\n");
        printf("|   4 - Extrato                    |\n");
        printf("|   0 - Sair                       |\n");
        printf("|==================================|\n");
        printf("| > Escolha uma opcao: ");
        scanf("%d", &opcao);
        clearBuffer();

        if(opcao <= 4 && opcao >= 0){
            validation = 1;
        }
        else{
            printf("\033[31m| | > Opçao Invalida, tente novamente.\n");
        }
    }while(validation = 0);
    
    return opcao;
}