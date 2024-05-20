#include "functions.h"
#define ASCII_MIN 33
#define ASCII_MAX 126
#define ALPHABET_SIZE (ASCII_MAX - ASCII_MIN + 1)

Value login(Conta contas[], int *pos, int *user) { // Função de Login
    int cpfCorrect = 1;
    int isAdmin = 0;
    int cont = 0;
    char cpf[T_CPF];

    do{
        printf("| > CPF (Ex: 112345678900): ");
        scanf("%s", cpf);
        clearBuffer();

        cpfCorrect = 1;
        int find = 0;

        if (strcmp(cpf, "admin") == 0) { // Verifica se o CPF é "admin"
            isAdmin = 1;
        }
        else {
            isAdmin = 0;
            if(strlen(cpf) != 11) { // Verifica se o tamanho do cpf é válido
                cpfCorrect = 0;
            }
            if(cpfCorrect) {
                for (int i = 0; cpf[i] != '\0'; i++) { // Verifica se não há nenhum char não cpférico no número informado;
                    if (!isdigit(cpf[i]) && cpf[i] != '\0') {
                        cpfCorrect = 0;
                        printf("\033[34m| > CPF Inválido, tente novamente...\n");
                        break;
                    }
                }
                find = findCPF( contas, *pos, cpf);
                if(find == -1) {
                    cpfCorrect = 0;
                    printf("\033[34m| > CPF Não Encontrado, tente novamente...\n");
                }
                else {
                    *user = find;
                }
            }
            else {
                printf("\033[34m| > CPF Inválido, tente novamente...\n");
                cpf[0] = '\0';
            }
        }

    } while(!cpfCorrect);
    
    // Solicitação de Senha:
    int passwordValidate = 0;
    int adminTrue = 0;
    int cpfPos;
    char password[SENHA];

    do {
        printf("| > Senha: ");
        fgets(password, SENHA, stdin);
        password[strcspn(password, "\n")] = '\0'; // Remove o \n do final do cpf informado;
        if (!isAdmin) { // Se tentar entrar com Administrador, Verifica a senha com o de Admin
            int compare = compareHash(password, contas[*user].senha);

            if(compare) {
                passwordValidate = 1;
            }
            else {
                printf("\033[34m| > Senha Inválida, tente novamente...\n");
            }
        }
        else { 
            const char* adminPassword =  "Mpyuz>@"; // Senha é "Admin24"
            if(compareHash(password, adminPassword)) {
                adminTrue = 1;
                passwordValidate = 1;
            }
            else {
                printf("\033[34m| > Senha Inválida, tente novamente...\n");
            }
        }
    } while(!passwordValidate);

    if(adminTrue) {
        *user = -1;
    }

    return OK;
}; 


const char* hash(const char* senha) {
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
    hash_senha[size] = '\0';
    return hash_senha;
}

int compareHash(const char* senha, const char* hash_cpf) {
    const char* hash_senha = hash(senha);
    int result = strcmp(hash_senha, hash_cpf);
    return result == 0;
}

int auth_senha(Conta contas[], int pos, int *user){
    int passwordValidate = 0;
    int cpfPos;
    char password[SENHA];
    do{
        printf("| > Senha: ");
        fgets(password, SENHA, stdin);
        password[strcspn(password, "\n")] = '\0'; // Remove o \n do final da senha informada;

            int compare = compareHash(password, contas[*user].senha);

            if(compare){
                passwordValidate = 1;
            }
            else{
                printf("\033[34m| > Senha Inválida, tente novamente...\n");
            }
        
    }while(!passwordValidate);

    return 1;
}; 
