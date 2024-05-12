#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"





//Funções ADM


Value novo_cliente(Conta contas[], int *pos, int *user){ 
    printf("novo");
}    // Função de Criar um novo cliente
Value deletar_cliente(Conta contas[], int *pos, int *user) {
     printf("delete");
} // Função de Deletar um cliente
Value listar_cliente(Conta contas[], int *pos, int *user) {
     printf("Lista");
} // Função de Listar os clientes



// Funções fundamentais

Value debito(Conta contas[], int *pos, int *user) {
     printf("debito");
}         // Função de debitar dinheiro de uma conta
Value deposito(Conta contas[], int *pos, int *user) {
     printf("deposito");
}       // Função de depositar um valor em uma conta
Value extrato(Conta contas[], int *pos, int *user) {
     printf("extrado");
}       // Função de gerar extrato do cliente
Value transacao(Conta contas[], int *pos, int *user) {
     printf("transacao");
}     // Função de realizar transacao entre contas

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
