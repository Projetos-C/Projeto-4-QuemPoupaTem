#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#define ASCII_MIN 33
#define ASCII_MAX 126
#define ALPHABET_SIZE (ASCII_MAX - ASCII_MIN + 1)

Value login(Conta contas[], int *pos, int *user){
    printf("Login");
    return OK;
}; 







Value cadastro(Conta contas[], int *pos, int *user){
    if(*pos >= TOTAL){
        return MAX_CONTA;
    }
    printf("| > Nome do Usuario: ");
    fgets(contas[*pos].nome, T_NOME, stdin);
    contas[*pos].nome[strcspn(contas[*pos].nome, "\n")] = '\0';



    int cpfCorrect;
    char cpf[T_CPF];
    do{
        cpfCorrect = 1;
        printf("| > CPF (Ex: 112345678900): ");
        fgets(cpf, T_CPF, stdin);

        cpf[strcspn(cpf, "\n")] = '\0'; // Remove o \n do final do número informado;
        if(strlen(cpf) > 11){ // Verifica se o tamanho do cpf é válido
            cpfCorrect = 0;
        }
        if(cpfCorrect){
            for (int i = 0; cpf[i] != '\0'; i++) { // Verifica se não há nenhum char não cpférico no número informado;
                if (!isdigit(cpf[i]) && cpf[i] != '\0') {
                    cpfCorrect = 0;
                    break;
                }
            }
        }

        else{
            printf("\033[34m| > CPF Inválido, tente novamente...\n");
            cpf[0] = '\0';
        }
    }while(!cpfCorrect);
    strcpy(contas[*pos].cpf, cpf);
    contas[*pos].cpf[strcspn(contas[*pos].cpf, "\n")] = '\0';



    char tipo_conta;
    int isValidType = 0;

    printf("| > Tipo conta:                           |\n");
    printf("| > Comum (c):                            |\n");
    printf("| > *taxa de 5%% no debito                 | \n");
    printf("| > *limite de saldo negativo de R$1.000  |\n");
    printf("| > Plus (p):                             |\n");
    printf("| > *taxa de 3%% no debito                 | \n");
    printf("| > *limite de saldo negativo de R$5.000  |\n");

    do {
        printf("\033[34m| > Escolha o tipo de conta (p/c): ");
        scanf(" %c", &tipo_conta); // Adicionando um espaço antes de %c para ignorar espaços em branco
        clearBuffer();
        
        if (tipo_conta == 'c' || tipo_conta == 'p') {
            isValidType = 1;
        } else {
            printf("\033[31m| > Tipo de conta invalido, Tente novamente...\n");
        }
    } while (!isValidType);

    


    float saldo;
    int isValid = 0; // Inicialize isValid como 0 para que o loop execute pelo menos uma vez

    do {
        printf("\033[34m| > Informe o saldo da conta: ");
        if (scanf("%f", &saldo) == 1) {
            clearBuffer();
            if (saldo >= 0) {
                printf("\033[32m| > Saldo valido!\n");
                printf("\033[34m");
                isValid = 1; // Atualize isValid para 1 se o saldo for válido
            } else {
                printf("\033[31m| > Saldo invalido, Tente novamente...\n");
            }
        } else {
            printf("\033[31m| > Entrada invalida, Tente novamente...\n");
            clearBuffer();
        }
    } while (!isValid); // Repita o loop enquanto isValid for 0 (saldo inválido)

    
    
    
    

    int senhaCorrect;
    char senha[SENHA];
    do {
        senhaCorrect = 1;
        printf("| > Digite sua senha: ");
        fgets(senha, SENHA, stdin);

        senha[strcspn(senha, "\n")] = '\0'; // Remove o \n do final da string

        if (strlen(senha) < 6) {
            printf("\033[34m| > Senha muito fraca, tente novamente com pelo menos 6 caracteres...\n");
            senhaCorrect = 0; // Define senhaCorrect como 0 para repetir o loop
        } else if (strlen(senha) >= SENHA) {
            printf("\033[34m| > Tamanho máximo de senha excedido, por favor, tente novamente...\n");
            senhaCorrect = 0; // Define senhaCorrect como 0 para repetir o loop
        }
    } while (!senhaCorrect);
    contas[*pos].senha = hash(senha);
    return OK;
}; 













char* hash(const char* senha){
     int length = strlen(senha);
      char* hash_senha = (char*)malloc((length + 1) * sizeof(char)); // +1 for the null terminator

     for (int i = 0; i < length; i++) {
        char char_atual = senha[i];

        // Apply the Caesar cipher
        int shifted_index = ((char_atual - ASCII_MIN) + 12) % ALPHABET_SIZE;
        if (shifted_index < 0) {
            shifted_index += ALPHABET_SIZE;
        }
        hash_senha[i] = (char)(shifted_index + ASCII_MIN);
     }
    hash_senha[length] = '\0'; // Null terminate the string
    printf(hash_senha);
    return hash_senha;
}






Value hash_compare(char hash[], char senha[], int *pos){
     printf("compare");
}