#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"



Value novo_cliente(Conta contas[], int *pos, int *user){};     // Função de Criar um novo cliente
Value deletar_cliente(Conta contas[], int *pos, int *user) {}; // Função de Deletar um cliente
Value listar_cliente(Conta contas[], int *pos, int *user) {};  // Função de Listar os clientes
Value debito(Conta contas[], int *pos, int *user) {};          // Função de debitar dinheiro de uma conta
Value deposito(Conta contas[], int *pos, int *user) {};        // Função de depositar um valor em uma conta
Value extrato(Conta contas[], int *pos, int *user) {};         // Função de gerar extrato do cliente
Value transacao(Conta contas[], int *pos, int *user) {};       // Função de realizar transacao entre contas
Value salvar(Conta contas[], int *pos, int *user);             // Função de Salvar a lista de contatos no arquivo binário
Value carregar(Conta contas[], int *pos, int *user);           // Função de Carregar a lista de contatos do arquivo binário
Value hash(char senha[], int *pos);
Value hash_compare(char hash[], char senha[], int *pos);
void clearBuffer() {}; // Função de Limpeza de Buffer
void tratarRes(Value err) {}; // Tratamento de Erros das funções de tipo Value



int menu_login(Conta contas[], int *pos){
    int opcao;
    
    do{
        printf("\n\033[34m|==================================|\n");
        printf("|- - -| Banco Quem Poupa Tem |- - -|\n");
        printf("|==================================|\n");
        printf("| > Menu de Login:                 |\n");
        printf("|   1 - Fazer Login                |\n");
        printf("|   2 - Fazer Cadastro             |\n");
        printf("|   0 - Sair                       |\n");
        printf("|==================================|\n");
        printf("| > Escolha uma opcao: ");
        scanf("%d", &opcao);
        //clearBuffer();
        
    }while(opcao != 0);
}
