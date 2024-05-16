#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#define ASCII_MIN 33
#define ASCII_MAX 126
#define ALPHABET_SIZE (ASCII_MAX - ASCII_MIN + 1)

Value login(Conta contas[], int *pos, int *user){ // Gunção de Login
    int cpfCorrect = 1;
    int isAdmin = 0;
    int cont = 0;
    char cpf[T_CPF];
    do{
        cpfCorrect = 1;
        printf("| > CPF (Ex: 112345678900): ");
        fgets(cpf, T_CPF, stdin);

        cpf[strcspn(cpf, "\n")] = '\0'; // Remove o \n do final do cpf informado;

        if (strcmp(cpf, "admin") == 0) { // Verifica se o CPF é "admin"
            isAdmin = 1;
        }
        else{
            if(strlen(cpf) > 11 && strlen(cpf) < 11){ // Verifica se o tamanho do cpf é válido
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
        }
    }while(!cpfCorrect);

    int passwordValidate = 0;
    int adminTrue = 0;
    int cpfPos;
    char password[SENHA];
    do{
        printf("| > Senha: ");
        fgets(password, SENHA, stdin);

        password[strcspn(password, "\n")] = '\0'; // Remove o \n do final do cpf informado;

        if (isAdmin) { // Se tentar entrar com Administrador, Verifica a senha com o de Admin
            const char* adminPassword =  "Mpyuz>@"; // Senha é "Admin24"
            if(compareHash(password, adminPassword)){
                adminTrue = 1;
                passwordValidate = 1;
            }
            else{
                printf("\033[34m| > Senha Inválida, tente novamente...\n");
            }
        }
        else{
            // Usuário Comum
        }
    }while(!passwordValidate);

    if(adminTrue){
        *user = -1;
    }
    else{
        *user = cpfPos; // Posição de um usuário comum
    }
    return OK;
}; 


char* hash(const char* senha){ // Cria um Has da Senha Criada
     int size = strlen(senha);
      char* hash_senha = (char*)malloc((size + 1) * sizeof(char));

     for (int i = 0; i < size; i++) {
        char char_atual = senha[i];

        // Cifra de Cesar com 12 casas em cada caracter
        int shifted_index = ((char_atual - ASCII_MIN) + 12) % ALPHABET_SIZE;
        if (shifted_index < 0) {
            shifted_index += ALPHABET_SIZE;
        }
        hash_senha[i] = (char)(shifted_index + ASCII_MIN);
     }
    hash_senha[size] = '\0'; // Null terminate the string
    //printf("%s", hash_senha);
    return hash_senha;
}


int compareHash(const char* senha, const char* hash) {
    int size = strlen(senha);

    for (int i = 0; i < size; i++) {
        char char_atual = senha[i];

        // AMesma cifra de cesar de 12 
        int shifted_index = ((char_atual - ASCII_MIN) + 12) % ALPHABET_SIZE;
        if (shifted_index < 0) {
            shifted_index += ALPHABET_SIZE;
        }

        // Compara cada caractere do hash gerado com o hash recebido
        if (hash[i] != (char)(shifted_index + ASCII_MIN)) {
            return 0; // Retorna 0 se os hashes não forem iguais
        }
    }

    // Se todos os caracteres forem iguais, retorna 1
    return 1;


}