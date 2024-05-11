#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"


Value novo_cliente(Conta contas[], int *pos, int *user){ 
    printf("novo");
}    // Função de Criar um novo cliente
Value deletar_cliente(Conta contas[], int *pos, int *user) {
     printf("delete");
} // Função de Deletar um cliente
Value listar_cliente(Conta contas[], int *pos, int *user) {
     printf("Lista");
} // Função de Listar os clientes
Value debito(Conta contas[], int *pos, int *user) {
     printf("débito");
}         // Função de debitar dinheiro de uma conta
Value deposito(Conta contas[], int *pos, int *user) {
     printf("deposito");
}       // Função de depositar um valor em uma conta
Value extrato(Conta contas[], int *pos, int *user) {
     printf("extrado");
}       // Função de gerar extrato do cliente
Value transacao(Conta contas[], int *pos, int *user) {
     printf("transação");
}     // Função de realizar transacao entre contas


// Funções de Autenticação -----------------------------------------
Value login(Conta contas[], int *pos, int *user){
    printf("Login");
    return OK;
}; 
Value cadastro(Conta contas[], int *pos, int *user){
    printf("cadastro");
    return OK;
}; 

Value hash(char senha[], int *pos){
     printf("hash");
}
Value hash_compare(char hash[], char senha[], int *pos){
     printf("compare");
}

// Menu
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
            printf("\033[31m| > Opção Inválida, Tente novamente...\n");
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
        printf("|   1 - Depósito                   |\n");
        printf("|   2 - Débito                     |\n");
        printf("|   3 - Transferência              |\n");
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
            printf("\033[31m| | > Opção Inválida, tente novamente.\n");
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
        printf("| > Menu de Usuário:               |\n");
        printf("|   1 - Depósito                   |\n");
        printf("|   2 - Débito                     |\n");
        printf("|   3 - Transferência              |\n");
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
            printf("\033[31m| | > Opção Inválida, tente novamente.\n");
        }
    }while(validation = 0);
    
    return opcao;
}


//Funções auxiliares
void tratarRes(Value err) {}; // Tratamento de Erros das funções de tipo Value

void clearBuffer(){ // Função de Limpeza de Buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

Value salvar(Conta contas[], int *pos, int *user){
     printf("salva");
}            // Função de Salvar a lista de contatos no arquivo binário
Value carregar(Conta contas[], int *pos, int *user){
     printf("carregar");
}           // Função de Carregar a lista de contatos do arquivo binário 
