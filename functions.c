#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

Value novo_cliente(Conta contas[], int *pos){};     // Função de Criar um novo cliente
Value deletar_cliente(Conta contas[], int *pos) {};   // Função de Deletar um cliente
Value listar_cliente(Conta contas[], int *pos) {};    // Função de Listar os clientes
Value debito(Conta contas[], int *pos) {};    // Função de debitar dinheiro de uma conta
Value deposito(Conta contas[], int *pos) {};  // Função de depositar um valor em uma conta
Value extrato(Conta contas[], int *pos) {}; // Função de gerar extrato do cliente
Value transacao(Conta contas[], int *pos) {}; // Função de realizar transacao entre contas

void clearBuffer() {}; // Função de Limpeza de Buffer
void tratarRes(Value err) {}; // Tratamento de Erros das funções de tipo Value