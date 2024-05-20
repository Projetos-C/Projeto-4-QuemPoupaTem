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
        printf("|   5 - Criar Usuario              |\n");
        printf("|   6 - Listar Usuarios            |\n");
        printf("|   7 - Deletar Usuario            |\n");
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


void enterSave(Conta contas[], int *pos){
  printf("\n|==================================|\n");
  printf("|  PRESSIONE ENTER PARA SALVAR     |\n");
  printf("|==================================|\n");
  char vazio;
  scanf("%c", &vazio);
  salvar(contas, &*pos);
}

void tratarRes(Value err){ // Tratamento de Erros das funções de tipo Value
    if (err == MAX_CONTAS) {
        printf("\033[31m| ERRO - Máximo de contas atingido.\n");
    } else if (err == CRIAR) {
        printf("\033[31m| ERRO - Não foi possível criar o arquivo.\n");
    } else if (err == SEM_CONTAS) {
        printf("\033[31m| ERRO - Não existem contas salvas.\n");
    } else if (err == ABRIR) {
        printf("\033[31m| ERRO - Não foi possível abrir o arquivo.\n");
    } else if (err == FECHAR) {
        printf("\033[31m| ERRO - Não foi possível fechar o arquivo.\n");
    } else if (err == ESCREVER) {
        printf("\033[31m| ERRO - Não foi possível escrever em seu arquivo.\n");
    } else if (err == LER) {
        printf("\033[31m| ERRO - Não foi possível ler o seu arquivo.\n");
    }  else if (err == SEM_EXTRATOS) {
        printf("\033[31m| ERRO - Lista de extratos está vazia.\n");
    } else if (err == ACESSO_INVALIDO) {
        printf("\033[31m| ERRO - Não foi possível validar o seu acesso.\n");
    }  else if (err == SEM_EXTRATOS) {
        printf("\033[31m| ERRO - Tamanho do extrato excedido.\n");
    } else if (err == OK) {
        // Fazer nada em caso de sucesso 
    } 
    else{
        printf("\033[31m| ERRO - Erro de Sistema Desconhecido.\n");
    }
    
}// Tratamento de Erros das funções de tipo Value