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
    printf("%d posições", *pos);
    if (*pos == 0) {
        return;
    }
    for (int i = 0; i < *pos; i++) {

        printf("|===============================\n");
        printf("| > Nome: %s  \n", contas[i].nome);
        
        printf("| > CPF: %s  \n", contas[i].cpf);
        switch (contas[i].tipo_conta)
        {
        case 'c':
          printf("| > Tipo da conta: Comum");
          break;
        case 'p':
          printf("| > Tipo da conta: Plus");
        default:
          break;
        }
    }
    return OK;
}


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

Value salvar(Conta contas[], int *pos){
   FILE *arq = fopen("contas.bin", "wb");
    if(arq == NULL)
        return ABRIR;
    
    int qtd = fwrite(contas, TOTAL, sizeof(Conta), arq);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), arq);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(arq))
        return FECHAR;

    printf("\033[32m| > Arquivo Salvo!!\n");
    return OK;
}            // Função de Salvar a lista de contatos no arquivo binário
Value carregar(Conta contatos[], int *pos){
    FILE *f = fopen("contas.bin", "rb");
    if(f == NULL)
    return ABRIR;

    int qtd = fread(contatos, TOTAL, sizeof(Conta), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
       return LER;

    if(fclose(f))
        return FECHAR;

    printf("\033[32m| > Contas carregados!!\n");
    return OK;

}        // Função de Carregar a lista de contatos do arquivo binário 
